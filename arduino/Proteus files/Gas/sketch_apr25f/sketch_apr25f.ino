int GasSensor = 5; // connect ir sensor to arduino pin 2
int LED = 12;
int LED2 = 11;// conect Led to arduino pin 13



void setup() 
{
  Serial.begin(9600);
  pinMode (GasSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT);
    pinMode (LED2, OUTPUT);// Led pin OUTPUT
}

void loop()
{
  int data = digitalRead (GasSensor);
  if (data==HIGH){
    digitalWrite(LED, HIGH);
    digitalWrite(LED2, LOW); 
    Serial.print("Gas detected");
  }
  
  if(data==LOW)
  {
    digitalWrite(LED2, HIGH); 
    digitalWrite(LED, LOW); 
    Serial.print("No Gas detected");
  }
  delay(100);
}
