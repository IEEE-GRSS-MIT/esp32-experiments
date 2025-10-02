/*
  ESP32 Ultrasonic Distance Web Server

  Code developed by Siddharth Huddar  
  Technical Head, IEEE GRSS, MIT Manipal

  Description:
  This project uses an ESP32 and an ultrasonic sensor to measure distance and 
  serve the data over a local WiFi network using a web server.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Enter_Your_SSID";
const char* password = "Enter_Your_Password";

// Ultrasonic Sensor Pins
const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

// Distance threshold in cm to determine if spot is occupied
const float OCCUPIED_THRESHOLD_CM = 15.0;

WebServer server(80);

// Measure distance in cm
float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1.0;

  return (duration * 0.0343f) / 2.0f;
}

// Serve main HTML UI
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Parking Spot Monitor</title>
      <style>
        body { font-family: Arial, sans-serif; text-align: center; padding-top: 50px; }
        #status { font-size: 2em; margin-top: 20px; }
        #distance { font-size: 1.5em; margin-top: 10px; }
        .occupied { color: red; }
        .available { color: green; }
      </style>
    </head>
    <body>
      <h1>🚗 Parking Spot Monitor</h1>
      <div id="status" class="available">Loading...</div>
      <div id="distance">Distance: -- cm</div>

      <script>
        function updateStatus() {
          fetch("/status")
            .then(res => res.json())
            .then(data => {
              const statusDiv = document.getElementById("status");
              const distanceDiv = document.getElementById("distance");

              distanceDiv.textContent = "Distance: " + data.distance + " cm";

              if (data.status === "occupied") {
                statusDiv.textContent = "🔴 Occupied";
                statusDiv.className = "occupied";
              } else if (data.status === "available") {
                statusDiv.textContent = "🟢 Available";
                statusDiv.className = "available";
              } else {
                statusDiv.textContent = "⚠️ Out of range";
                statusDiv.className = "";
              }
            })
            .catch(err => {
              document.getElementById("status").textContent = "Error fetching data";
              document.getElementById("distance").textContent = "";
            });
        }

        setInterval(updateStatus, 1000); // Poll every second
        updateStatus(); // Initial fetch
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html; charset=utf-8", html);
}

// Serve sensor status as JSON
void handleStatus() {
  float distance = measureDistanceCm();
  String status;

  if (distance < 0.0f) {
    status = "out_of_range";
  } else if (distance <= OCCUPIED_THRESHOLD_CM) {
    status = "occupied";
  } else {
    status = "available";
  }

  String json = "{";
  json += "\"distance\":" + String(distance, 1) + ",";
  json += "\"status\":\"" + status + "\"";
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
