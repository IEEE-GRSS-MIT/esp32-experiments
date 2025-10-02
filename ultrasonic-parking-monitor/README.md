# ESP32 Ultrasonic Sensor Web Server

This project demonstrates how to use an ESP32 microcontroller with an HC-SR04 ultrasonic sensor to measure distance and serve real-time status updates over a WiFi web server.

---

## 📡 Features

- ESP32-based WiFi-enabled distance measurement
- Real-time status displayed via web browser
- Simple HTML interface served from SPIFFS
- Sensor: HC-SR04 (Ultrasonic)

---

## 🔧 Hardware Required

- ESP32 Dev Board
- HC-SR04 Ultrasonic Sensor
- Jumper Wires
- Breadboard (optional)

### 🛠 Wiring

| HC-SR04 Pin | ESP32 GPIO |
|-------------|------------|
| VCC         | 5V         |
| GND         | GND        |
| TRIG        | GPIO 5     |
| ECHO        | GPIO 18    |

---

## 🚀 Getting Started

### 📁 Folder Structure

