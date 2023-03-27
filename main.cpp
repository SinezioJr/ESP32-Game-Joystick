#include <Arduino.h>

#define XPORT 34
#define YPORT 32

#include <WiFi.h>

#include <WiFiClient.h>

// WiFiClient client;

const char* ssid = "5 reais";
const char* password = "12344321";

const char* host = "192.168.133.158";
const int port = 8080;

void setup() {
  pinMode(XPORT, INPUT);
  pinMode(YPORT, INPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi...");

  Serial.println("Connected to WiFi");
}

}

void loop() {

  int xVal = analogRead(XPORT); // read X port
  int yVal = analogRead(YPORT); // read Y port

  // map the joystick values from 0-4095 to -100 to 100
  int xMapped = map(xVal, 0, 4095, 0, 200);
  int yMapped = map(yVal, 0, 4095, 0, 200);

  // print the mapped joystick values
  Serial.print("X: ");
  Serial.print(xMapped);
  Serial.print(" Y: ");
  Serial.println(yMapped);

  String pos = String(xMapped) + "," + String(yMapped);
 
  WiFiClient client;
  
  if (!client.connected()) { // check if the client is connected to the server
    if (!client.connect(host, port)) { // if not, try to connect
      Serial.println("Connection failed.");
      return;
    }
    
    Serial.println("Connected to server.");
  }
  
  
  client.print(pos); // send the analog value as a string to the server
  client.stop(); // close the connection
  delay(1000); // wait for a second before sending the next value

}
