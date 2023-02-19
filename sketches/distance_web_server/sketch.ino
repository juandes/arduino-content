#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h"

const char* ssid     = "SSID";
const char* password = "PASSWORD";

WebServer server(80);

#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Set the distance sensor
  Wire.begin();
  if (distanceSensor.init() == false) {
    Serial.println("Distance sensor is online.");
  }

  server.on("/distance", [](){
   distanceSensor.startRanging();
   int distance = distanceSensor.getDistance(); // distance is in mm.
   distanceSensor.stopRanging();
    server.send(200, "text/plain", String(distance));
  });

  server.on("/ping", [](){
    server.send(200, "text/plain", "ok");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}