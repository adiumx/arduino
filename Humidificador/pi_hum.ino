#include <DHT.h>
#include <tinyml4all.h>

#define DHTPIN 5
#define DHTTYPE DHT11
#define RELAY_PIN 3

using tinyml4all::printCSV;

DHT dht(DHTPIN, DHTTYPE);

// -------- CONFIGURACIÓN --------
float setpoint = 60.0;
float Kp = 2.5;
float Ki = 0.02;
unsigned long windowTime = 60000; // 60 s
unsigned long logInterval = 2000; // ✅ intervalo CSV
// --------------------------------

float integral = 0.0;
unsigned long windowStartTime = 0;
unsigned long lastRead = 0;
unsigned long lastLogTime = 0;
unsigned long onTime = 0;

int state = 0;
int lastState = 0;

// ⏱ Tiempo ON vivo
unsigned long onStartTime = 0;
unsigned long onDuration = 0;

float humidity = NAN;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  dht.begin();
  Serial.begin(9600);

  windowStartTime = millis();
  lastLogTime = millis();

  printCSV("timestamp,humidity,state,setpoint,on_time_ms");
}

void loop() {
  unsigned long now = millis();

  // -------- LECTURA DHT --------
  if (now - lastRead >= 2000) {
    lastRead = now;
    humidity = dht.readHumidity();
    if (isnan(humidity)) return;

    if (humidity >= setpoint) {
      onTime = 0;
      integral = 0;
    } else {
      float error = setpoint - humidity;
      integral += error;
      integral = constrain(integral, 0, 100);

      onTime = (Kp * error + Ki * integral) * 1000;
      onTime = constrain(onTime, 0, windowTime);
    }
  }

  // -------- VENTANA --------
  if (now - windowStartTime >= windowTime) {
    windowStartTime = now;
  }

  // -------- CONTROL --------
  if ((now - windowStartTime) < onTime) {
    state = 1;
    digitalWrite(RELAY_PIN, LOW);
  } else {
    state = 0;
    digitalWrite(RELAY_PIN, HIGH);
  }

  // -------- TIEMPO EN 1 --------
  if (state == 1 && lastState == 0) {
    onStartTime = now;
  }

  if (state == 1) {
    onDuration = now - onStartTime;
  } else {
    onDuration = 0;
  }

  lastState = state;

  // ✅ -------- LOG A INTERVALOS REGULARES --------
  if (now - lastLogTime >= logInterval) {
    lastLogTime = now;
    printCSV(now, humidity, state, setpoint, onDuration);
  }
}
