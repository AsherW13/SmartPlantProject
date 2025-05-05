#define WATER_SENSOR_PIN  35
#define MOISTURE_SENSOR_PIN 32
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"



// not touching 1000
// barely touching 1600
// halfway 3000
// max is 4095
#define motor 18


WiFiClient client;
const char* server = "34.56.124.39";
const int port = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  // initialize digital pin as an output.
  pinMode(motor, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected!");
}

void sendData(int sensorVal) {
  if (client.connect(server, port)) {
    Serial.println("Connected to server!");

    String jsonPayload = "{\"Water Level\": " + String(sensorVal) + "}";

    int contentLength = jsonPayload.length();

    // Construct HTTP POST request
    client.println("POST /data HTTP/1.1");
    client.println("Host: 34.56.124.39");
    client.println("Content-Type: application/json");
    client.print("Content-Length: "); // Length of the JSON payload
    client.println(contentLength);
    client.println();
    client.println(jsonPayload);

    // Wait for a response
    while (client.available()) {
      String response = client.readString();
      Serial.println(response);
    }

    client.stop(); // Close the connection
  } else {
    Serial.println("Connection to server failed.");
  }
}

int readWaterSensor() {
  int WaterSensorValue = analogRead(WATER_SENSOR_PIN);
  Serial.print("Water sensor Level: ");
  Serial.println(WaterSensorValue);

  return WaterSensorValue;
  delay(1000);

}

int readMoistureSensor() {
  int moistureSensorValue = analogRead(MOISTURE_SENSOR_PIN);
  Serial.print("Moisture sensor Level: ");
  Serial.println(moistureSensorValue);

  return moistureSensorValue;
  delay(1000);
}

void turnMotorOn() {
  digitalWrite(motor, HIGH);
  delay(1000);
  
  digitalWrite(motor, LOW);
  delay(3000);
  delay(5);
}

void loop() {
  int waterValue = readWaterSensor();

  int moistureValue = readMoistureSensor();

  turnMotorOn();

  if (WiFi.status() == WL_CONNECTED) {
    sendData(waterValue);
    delay(1000);
    sendData(moistureValue);
  }

  delay(5000); // send every 10 seconds
}
