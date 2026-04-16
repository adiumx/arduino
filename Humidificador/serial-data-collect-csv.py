#!/usr/bin/env python
"""
Serial Data Collection + Command Sender (START / END)
"""

import os
import serial
import serial.tools.list_ports
import time

BAUD = 9600
ON_TIMES_MS = [120000]
LABEL = "dataset"

# detectar puerto
ports = list(serial.tools.list_ports.comports())
if not ports:
    print("No se detectaron puertos")
    exit(1)

port = ports[0].device
print(f"Usando puerto: {port}")

# abrir serial
ser = serial.Serial(port, BAUD, timeout=2)
time.sleep(5)  # esperar Arduino + DHT

csv_path = f"{LABEL}.csv"
if not os.path.exists(csv_path):
    with open(csv_path, "w") as f:
        f.write("ensayo,evento,humedad,tiempo_on_ms\n")

for t_on in ON_TIMES_MS:
    cmd = f"ON {t_on}\n"
    print(f"Enviando: {cmd.strip()}")
    ser.write(cmd.encode())

    start_line = None
    end_line = None

    while True:
        line = ser.readline().decode(errors="ignore").strip()
        if not line:
            continue

        print("RX:", line)

        if line.startswith("ensayo"):
            continue

        if ",START," in line:
            start_line = line

        if ",END," in line:
            end_line = line
            break

    if start_line and end_line:
        with open(csv_path, "a") as f:
            f.write(start_line + "\n")
            f.write(end_line + "\n")

ser.close()
print("Listo ✅")