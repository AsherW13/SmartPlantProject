//#include <WiFi.h>
//#include <HTTPClient.h>
//#include <ArduinoJson.h>


#define WATER_SENSOR_PIN  35
// not touching 1000
// barely touching 1600
// halfway 3000
// max is 4095

#define MOISTURE_SENSOR_PIN 32
// average level is 190
// or maybe 1500

#define motor 26


const char* ssid = "CPS-Cyber-01";
const char* password = "unhappy3sandstonedeflector";

//WiFiClient client;
const char* server = "34.56.124.39";
const int port = 5000;


void setup() {

  /*
  Serial.begin(115200);
  pinMode(WATER_SENSOR_PIN, INPUT);
  // initialize digital pin as an output.
  

  //WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected!");
  */
  Serial.begin(115200);

  pinMode(MOISTURE_SENSOR_PIN, INPUT);

  pinMode(22, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
}

/*
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
*/

int readWaterSensor() {
  int WaterSensorValue = analogRead(WATER_SENSOR_PIN);
  Serial.print("Water sensor Level: ");
  Serial.println(WaterSensorValue);

  return WaterSensorValue;

}

int readMoistureSensor() {

  int averageMoist = 0;
  for(int i=0;i<=4;i++) {
    averageMoist += analogRead(MOISTURE_SENSOR_PIN);
    delay(100);
  }
  Serial.print("Moisture sensor Level: ");
  Serial.println(averageMoist/5);

  return averageMoist/5;
}

void turnMotorOn() {
  digitalWrite(motor, HIGH);
  //delay(2000);
  
  //digitalWrite(motor, LOW);
  //delay(3000);
}
 
void turnMotorOff() {
  digitalWrite(motor, LOW);
  //delay(3000);
}

void loop() {
  //int waterValue = readWaterSensor();

  //int moistureValue = readMoistureSensor();
  if(digitalRead(22) == LOW){
    turnMotorOn();
  } else {
    turnMotorOff();
  }

  
  readMoistureSensor();
  readWaterSensor();
  delay(1000);

  //if (WiFi.status() == WL_CONNECTED) {
    //sendData(waterValue);
    //delay(1000);
    //sendData(moistureValue);
  //}

  
}