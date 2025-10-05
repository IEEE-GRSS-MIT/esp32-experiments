# 🌡️ ESP32 DHT11 Wireless Web Server

A simple ESP32 project that reads temperature and humidity data from a **DHT11 sensor** and serves it over a **Wi-Fi Access Point** using an asynchronous web server. The data updates in **real-time** on a web page every 2 seconds.

## 📷 Demo

![Web UI Demo](https://via.placeholder.com/600x300.png?text=ESP32+DHT11+Web+Server+UI)

## 🚀 Features

- Uses **ESP32 as a Wi-Fi Access Point** (no internet needed)
- Displays **temperature and humidity** from DHT11 sensor
- Real-time updates using JavaScript and AJAX
- Lightweight and responsive web interface

---

## 🛠️ Hardware Required

| Component       | Description                   |
|----------------|-------------------------------|
| ESP32 Dev Board| Any ESP32 board               |
| DHT11 Sensor   | Temperature & Humidity sensor |
| Jumper Wires   | For connections               |
| Breadboard     | (Optional) for prototyping    |

### 🖧 Wiring

| DHT11 Pin | Connects to ESP32 |
|-----------|------------------|
| VCC       | 3.3V             |
| GND       | GND              |
| DATA      | GPIO 27          |

---

## 📦 Libraries Used

Make sure you install the following libraries in your Arduino IDE:

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)

---

## 🧠 How It Works

1. ESP32 creates its own Wi-Fi Access Point (`ESP32_AP` with password `12345678`)
2. Connect your phone or PC to the AP.
3. Open a browser and navigate to the IP shown in the Serial Monitor (usually `192.168.4.1`).
4. The web page fetches sensor data from:
   - `/temperature` → returns temperature in °C
   - `/humidity` → returns humidity in %

The data is dynamically updated every 2 seconds via JavaScript.

---

## 📄 Code Highlights

- **Web Page Served from PROGMEM**  
  Saves memory by embedding the HTML directly into flash.

- **AJAX-based Sensor Updates**  
  The browser makes fetch requests every 2 seconds:
  ```javascript
  setInterval(getData, 2000);
  ```

- **Asynchronous Server**  
  Handles multiple client requests efficiently using `ESPAsyncWebServer`.

---

## 🔧 Setup Instructions

1. Open the code in Arduino IDE.
2. Install all required libraries.
3. Select the right ESP32 board and COM port.
4. Upload the sketch.
5. Open the Serial Monitor at 115200 baud to find the AP IP address.
6. Connect your device to the Wi-Fi AP `ESP32_AP` (password: `12345678`).
7. Open the shown IP (usually `192.168.4.1`) in a browser.

---

## 📂 File Structure

```
ESP32-DHT11-WebServer/
├── ESP32_DHT11_WebServer.ino
├── README.md
```

---

## 📋 To-Do / Ideas

- Add Celsius/Fahrenheit toggle
- Use DHT22 for better accuracy
- Add MQTT support for remote transmission
- Store data using SPIFFS or microSD

---

## 🧾 License

This project is open-source and available under the MIT License.
