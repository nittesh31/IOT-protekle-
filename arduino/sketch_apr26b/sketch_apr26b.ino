#define trigPin 16
#define echoPin 5
#include<Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
char ssid[] = "stunny";
char pass[] = "Sabarips";
String postData;
String postVariable = "Level of tank=";

WiFiClient client;
char server[] = "https://protekle-toiletsystem.herokuapp.com/dataViewer";
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
    long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
   String data=String(distance);
    postData = postVariable + data;
  // put your main code here, to run repeatedly:
  HTTPClient http;
//  JSONVar myObject = JSON.parse(sensorReadings);
//
//// JSON.typeof(jsonVar) can be used to get the type of the var
//if (JSON.typeof(myObject) == "undefined") {
//  Serial.println("Parsing input failed!");
//  return;
//}
//
//Serial.print("JSON object = ");
//Serial.println(myObject);
      
      // Your Domain name with URL path or IP address with path
      http.begin(server);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "gas=1&smell=2&RGB=6&IR=4";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
//      http.addHeader("Content-Type", "application/json");
//      int httpResponseCode = http.POST("{\"name\":\"tPmAT5Ab3j7F9\"}");

      // If you need an HTTP request with a content type: text/plain
//      http.addHeader("Content-Type", "text/plain");
//      int httpResponseCode = http.POST("name:'Hello, World!'");
//     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
 

  Serial.println(postData);

  delay(3000);
}
