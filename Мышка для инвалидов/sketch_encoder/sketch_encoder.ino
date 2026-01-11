#define ENC_A 4
#define ENC_B 5

bool prev;

void pollEnc(bool e0, bool e1) {
    if (prev != e0) {
        Serial.println(e1 ^ e0);  // направление
        prev = e0;
    }
}

void setup() {
    Serial.begin(115200);
    prev = digitalRead(ENC_A);
}

void loop() {
    pollEnc(digitalRead(ENC_A), digitalRead(ENC_B));  // постоянный опрос в loop
}