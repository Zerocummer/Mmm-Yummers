#define ENC_A 3
#define ENC_B 4
int oldValue = 0;
bool p0, p1;

void pollEnc(bool e0, bool e1) {
    if (p0 ^ p1 ^ e0 ^ e1) {
        Serial.println(p1 ^ e0);    // направление
        p0 = e0;
        p1 = e1;
    }
}

void setup() {
    Serial.begin(115200);
    p0 = digitalRead(ENC_A);    // стартовые значения
    p1 = digitalRead(ENC_B);
    pinMode(2, INPUT_PULLUP);
}

void loop() {
  pollEnc(digitalRead(ENC_A), digitalRead(ENC_B));    // постоянный опрос в loop
  int newValue = digitalRead(2);
  if (newValue == oldValue){
    Serial.println(newValue);
    Serial.println(oldValue);
    int oldValue = newValue;
  }
}