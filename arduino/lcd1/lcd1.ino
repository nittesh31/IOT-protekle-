#include <LiquidCrystal.h>

#define trigPin 8
#define echoPin 7
#define led 13

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(9, 6, 5, 4, 3, 2);

int pos = 0;    // variable to store the servo position 

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

 
 lcd.begin(20, 4);

  lcd.setCursor(0, 1);

   delay(1000);
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
  if (distance < 24) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off

   delay(200);
       digitalWrite(led,LOW);
}
  else {
    digitalWrite(led,LOW);
  }

  lcd.setCursor(1, 0);
  lcd.print("Distance= ");
 
  lcd.print(distance);
  lcd.print("cm");
  
    Serial.print(distance);
    Serial.println(" cm");
 
  delay(1000);
}
