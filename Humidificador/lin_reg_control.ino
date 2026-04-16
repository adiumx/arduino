#include <DHT.h>
#include <tinyml4all.h>

#define DHTPIN 5
#define DHTTYPE DHT11
#define RELAY_PIN 3

using tinyml4all::printCSV;

DHT dht(DHTPIN, DHTTYPE);

// ==================================================
// 🧠 DATASET (TU TABLA DE CONOCIMIENTO)
// ==================================================
const int N = 10;

const float tiempo_s[N] = {
  10, 10, 15, 20, 20,
  20, 25, 30, 60, 120
};

const float delta_h[N] = {
  -2, -1, 3, 1, 2,
   2, 5, 7, 16, 22
};
// ==================================================

// ===== MODELO LINEAL (calculado desde el dataset) =====
float k = 0.0;
float c = 0.0;
// ======================================================

float humedadObjetivo = 65.0;
float lastValidHumidity = NAN;

// tiempos
const unsigned long senseInterval = 2000;
const unsigned long settleTime = 30000;

unsigned long lastSenseTime = 0;
unsigned long stateStartTime = 0;
unsigned long onDuration_ms = 0;

// estados
enum ControlState { IDLE, ACTUATING, SETTLING };
ControlState state = IDLE;

void calcularRegresion() {
  float sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;

  for (int i = 0; i < N; i++) {
    sum_x  += tiempo_s[i];
    sum_y  += delta_h[i];
    sum_x2 += tiempo_s[i] * tiempo_s[i];
    sum_xy += tiempo_s[i] * delta_h[i];
  }

  float denom = N * sum_x2 - sum_x * sum_x;
  if (denom != 0) {
    k = (N * sum_xy - sum_x * sum_y) / denom;
    c = (sum_y - k * sum_x) / N;
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  calcularRegresion();

  printCSV("INFO,k,c");
  printCSV("MODEL", k, c);
  printCSV("tipo,humedad,hum_obj,delta_h,tiempo_on_s");
}

void loop() {
  unsigned long now = millis();

  // =================================================
  // 1️⃣ SENSADO CONTINUO (NUNCA SE DETIENE)
  // =================================================
  if (now - lastSenseTime >= senseInterval) {
    lastSenseTime = now;
    float h = dht.readHumidity();
    if (!isnan(h)) {
      lastValidHumidity = h;
      printCSV("SENSE", h, "", "", "");
    }
  }

  // =================================================
  // 2️⃣ LÓGICA DE CONTROL NO BLOQUEANTE
  // =================================================
  if (state == IDLE && !isnan(lastValidHumidity)) {
    float deltaDeseada = humedadObjetivo - lastValidHumidity;

    if (deltaDeseada > 0 && k > 0) {
      float tiempo_on_s = (deltaDeseada - c) / k;
      tiempo_on_s = constrain(tiempo_on_s, 5, 180);

      onDuration_ms = (unsigned long)(tiempo_on_s * 1000);

      printCSV(
        "CTRL",
        lastValidHumidity,
        humedadObjetivo,
        deltaDeseada,
        tiempo_on_s
      );

      digitalWrite(RELAY_PIN, LOW);
      stateStartTime = now;
      state = ACTUATING;
    }
  }

  if (state == ACTUATING && now - stateStartTime >= onDuration_ms) {
    digitalWrite(RELAY_PIN, HIGH);
    stateStartTime = now;
    state = SETTLING;
  }

  if (state == SETTLING && now - stateStartTime >= settleTime) {
    state = IDLE;
  }
}
