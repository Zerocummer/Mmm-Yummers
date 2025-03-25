void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT)
}

void loop() {
  int val = analogRead(A0)
  if (val < 340){
    Serial.println(map(val, 0, 340, 1350, 300));
  }
  else{
    if (val <= 500){
      Serial.println(map(val, 340, 500, 300, 110));
    }
    else{
      Serial.println(map(500, 1023, 110, 0));
  }
  delay(50);
}