#include <DHT.h>
#include <tinyml4all.h>

#define DHTPIN 5
#define DHTTYPE DHT11
#define RELAY_PIN 3

using tinyml4all::printCSV;

DHT dht(DHTPIN, DHTTYPE);

// ---------- CONFIG ----------
unsigned long readInterval = 2000;
unsigned long settleTime   = 20000;
// ---------------------------

float humidity = NAN;
float lastValidHumidity = NAN;
unsigned long lastRead = 0;

int ensayo = 0;

enum State { IDLE, ON_ACTIVE, SETTLING };
State state = IDLE;

unsigned long stateStart = 0;
unsigned long onDuration = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  Serial.begin(9600);
  dht.begin();

  printCSV("ensayo,evento,humedad,tiempo_on_ms");
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    float h = dht.readHumidity();
    if (!isnan(h)) {
      humidity = h;
      lastValidHumidity = h;
    }
  }

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("ON") && state == IDLE) {
      onDuration = cmd.substring(2).toInt();

      if (onDuration > 0 && !isnan(lastValidHumidity)) {
        ensayo++;
        printCSV(ensayo, "START", lastValidHumidity, onDuration);

        digitalWrite(RELAY_PIN, LOW);
        state = ON_ACTIVE;
        stateStart = now;
      }
    }
  }

  if (state == ON_ACTIVE && now - stateStart >= onDuration) {
    digitalWrite(RELAY_PIN, HIGH);
    state = SETTLING;
    stateStart = now;
  }

  if (state == SETTLING && now - stateStart >= settleTime) {
    printCSV(ensayo, "END", lastValidHumidity, onDuration);
    state = IDLE;
  }
}
