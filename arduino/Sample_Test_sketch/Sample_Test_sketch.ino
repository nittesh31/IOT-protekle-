#define RfidPin D7

int id;
int passw;
int worker = 0;

void setup() {
  Serial.begin (9600);
  pinMode(RfidPin, INPUT);
  Serial.println("Hello, here the Test file serial monitor is active");
}

void loop() {
  
  worker = digitalRead(RfidPin);
  Serial.println(worker);
//  if (worker == HIGH){
//   
////      Serial.println("Enter your worker ID");
////      id = Serial.read();
////      delay(2000);
////      Serial.print("I received: ");
////  
////      Serial.println("Enter your worker Password");
////      passw = Serial.read();
////      delay(2000);
////      Serial.print("I received: ");
////  
////      if( id == 4 && passw == 123456){
////        Serial.println("Here we reset the value :):)");
////      }
//    Serial.println(worker);
//  }
  delay(1000);

}
