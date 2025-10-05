/*
  ESP32 Ultrasonic Distance Web Server

  Code developed by Siddharth Huddar  
  Technical Head, IEEE GRSS, MIT Manipal

  Description:
  This project uses an ESP32 and an ultrasonic sensor to measure distance and 
  serve the data over a local WiFi network using a web server.
*/

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center; }
    h2 { font-size: 2.5rem; }
    p { font-size: 2rem; }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server (Real-Time Updates)</h2>
  <p>Temperature: <span id="temperature">--</span> °C</p>
  <p>Humidity: <span id="humidity">--</span> %</p>

  <script>
    async function getData() {
      try {
        const tempResponse = await fetch("/temperature");
        const humResponse = await fetch("/humidity");
        const tempText = await tempResponse.text();
        const humText = await humResponse.text();
        document.getElementById("temperature").textContent = tempText;
        document.getElementById("humidity").textContent = humText;
      } catch (error) {
        console.log("Error fetching data:", error);
      }
    }
    // Fetch every 2 seconds
    setInterval(getData, 2000);
    getData(); // initial call
  </script>
</body>
</html>)rawliteral";

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Start Access Point
  const char* apSSID = "ESP32_AP";
  const char* apPassword = "12345678";
  WiFi.softAP(apSSID, apPassword);

  Serial.println();
  Serial.println("Access Point started!");
  Serial.print("SSID: "); Serial.println(apSSID);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  // Serve the HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Dynamic routes for sensor data
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    float temp = dht.readTemperature();
    if (isnan(temp)) temp = 0;
    request->send(200, "text/plain", String(temp, 1));
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    float hum = dht.readHumidity();
    if (isnan(hum)) hum = 0;
    request->send(200, "text/plain", String(hum, 1));
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // AsyncWebServer runs independently
}
