#define trigPin 16
#define echoPin 5
long duration; // variable for the duration of sound wave travel
long distance; // variable for the distance measurement
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include "RestClient.h"
char ssid[] = "stunny";
char pass[] = "Sabarips";
char jsonObject[128];
String data;
String dist;
const char* dist1;
String response;
RestClient client = RestClient("protekle-toiletsystem.herokuapp.com");
void setup() {

  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, pass);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  dist=String(distance);
  data = "{\r\n        \"gas\": 10,\r\n        \"smell\": "+dist+",\r\n        \"RGB\": 15,\r\n        \"IR\": 10\r\n}";
  dist1=data.c_str();
  Serial.println(dist1);
  Serial.println(" cm");
  delay(1000);
  response = "";
  int statusCode = client.post("/dataViewer", dist1 , &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(2000);
}
