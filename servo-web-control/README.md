# 🚀 ESP32 Servo Motor Web Server

This project allows you to control a **servo motor** using an **ESP32** via a simple **web interface**. The servo's position can be changed in real-time using a slider on a webpage hosted by the ESP32 itself.

> Based on the tutorial by [Random Nerd Tutorials](https://RandomNerdTutorials.com/esp32-servo-motor-web-server-arduino-ide/)

---

## 📦 Features

- Web-based slider control for servo motor (0° to 180°)
- Real-time updates using AJAX
- Built-in web server hosted on the ESP32
- Wi-Fi connectivity for wireless access
- Simple and responsive HTML + JS interface

---

## 🧰 Hardware Required

| Component              | Quantity |
|------------------------|----------|
| ESP32 Dev Board        | 1        |
| Servo Motor (e.g., SG90) | 1      |
| Jumper Wires           | As needed |
| External Power Source (for Servo) | 1 (recommended) |

---

## 🔌 Wiring

| Servo Wire | Connects to ESP32 |
|------------|------------------|
| GND        | GND              |
| VCC        | 5V (external recommended) |
| Signal     | GPIO 13          |

---

## 🛠️ Setup Instructions

1. **Install Arduino IDE**  
   Download from [arduino.cc](https://www.arduino.cc/en/software)

2. **Install ESP32 Board Package**  
   Follow this guide: [Installing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide/)

3. **Install Required Library**  
   - `ESP32Servo` library by John K. Bennett

4. **Configure Wi-Fi Credentials**  
   Replace the following lines in your code with your Wi-Fi SSID and password:
   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";
