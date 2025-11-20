const int ledPins[] = {3, 5, 6, 9, 10, 11};
const char buttonPin1 = A1;
const char buttonPin2 = A2;

void start(){
  for (int i = 0; i < 6; i++){
    analogWrite(ledPins[i], HIGH);
    delay(500);
  }
  delay(1000);
  for (int i = 0; i < 6; i++){
    analogWrite(ledPins[i], LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Монитор порта готов.");
  for (int i = 0; i < 6; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  start();
}