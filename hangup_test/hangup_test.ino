

void setup() {
  Serial.begin(9600);

  pinMode(40,INPUT_PULLUP);

}

void loop() {
  
  Serial.println(digitalRead(40));

  delay(100);

}
