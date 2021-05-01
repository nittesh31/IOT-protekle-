

#define trigPin 16
#define echoPin 5
long duration; // variable for the duration of sound wave travel
long distance; // variable for the distance measurement
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
char ssid[] = "RaahulJio 5G";
char pass[] = "12345678";
String postData;
String postVariable = "Level of tank=";

WiFiClient client;
char server[] = "https://protekle-toiletsystem.herokuapp.com/testdata";
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
  Serial.println(" cm");
  delay(1000);
   String data1=String(distance);
    postData = postVariable + data1;

    JSONVar myObject = JSON.parse("{\"api_key\":\"9bad6dff-ad74-4c51-ab4c-67a5997b976c\",\"name\":\"lacu\"}");
      if (JSON.typeof(myObject) == "undefined") {
          Serial.println("Parsing input failed!");
          return;
}

Serial.print("JSON object = ");
Serial.println(myObject);
  HTTPClient http;
      http.begin(client,server);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Content-Length","10");
//      http.addHeader("auth-key","9bad6dff-ad74-4c51-ab4c-67a5997b976c");

      int httpCode = http.POST("{\"name\": \"lachsc\"}"); 
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.println(httpCode);
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
      http.end();

  Serial.println(postData);
  delay(2000);
}
