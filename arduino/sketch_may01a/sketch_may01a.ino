#define trigPin 12
#define echoPin 14
#define smelPin A0
#define piroPin D8
#define RfidPin D7

long duration; // variable for the duration of sound wave travel
long distance; // variable for the distance measurement
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include "RestClient.h"
char ssid[] = "Raahul jio 4G";
char pass[] = "12345678";
char jsonObject[128];
String data;
String dist;
String gas = "null";
const char* dist1;
String response;
int pirStat = 0;
int capacity = 0;
String cap = "null";
int id;
int passw;


RestClient client = RestClient("protekle-toiletsystem.herokuapp.com");
void setup() {

  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(smelPin, INPUT);
  pinMode(piroPin, INPUT);
  pinMode(RfidPin, INPUT);
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

  int smellData = analogRead(smelPin);
//  gas = String(smellData);
  if (smellData>850){
    gas = "Gas detected";
    Serial.println("Gas detected");
  }
  
  if(smellData <880)
  {
    gas = "No Gas detected";
    Serial.println("No Gas detected");
  }


  pirStat = digitalRead(piroPin); 
  if (pirStat == HIGH) {            // if motion detected
   capacity = capacity + 1;
   Serial.println("Hey I got you!!!");
  } 


int worker = digitalRead(RfidPin);
if (worker == HIGH){
  
    
    Serial.println("Enter your worker ID");
    id = Serial.read();
    delay(2000);
    Serial.print("I received: ");

    Serial.println("Enter your worker Password");
    passw = Serial.read();
    delay(2000);
    Serial.print("I received: ");

    if( id == 4 && passw == 123456){
      cap == 0;
    }
  
}
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
  cap = String(capacity);
  dist=String(distance);
  data = "{\r\n        \"gas\": \""+ gas +"\",\r\n        \"ultrasonic\": "+dist+",\r\n        \"RGB\": 15,\r\n        \"IR\": "+cap+"\r\n}";
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
