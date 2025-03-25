void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int val = analogRead(A0);
  if (val < 340){
    int d1 = map(val, 0, 340, 1350, 300);
    Serial.println(d1);
  }
  else{
    if (val <= 500){
      int d2 = map(val, 340, 500, 300, 110);
      Serial.println(d2);
    }
    else{
      int d3 = map(val, 500, 1023, 110, 0);
      Serial.println(d3);
  }
  }
  delay(50);
}