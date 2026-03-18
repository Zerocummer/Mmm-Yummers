#include <Wire.h>
#include <MPU6050_light.h>
#include <Mouse.h>
#include <Keyboard.h>
MPU6050 mpu(Wire);
#define PIN_S1 4
#define PIN_S2 5
#define BTN_SENS 6
static const int8_t encTable[16] = {
  0, -1,  1,  0,
  1,  0,  0, -1,
 -1,  0,  0,  1,
  0,  1, -1,  0
};
uint8_t lastAB = 0;
int8_t  accum   = 0;
uint32_t encLastMs = 0;
const uint8_t BTN_L = 7;
const uint8_t BTN_M = 8;
const uint8_t BTN_R = 9;
uint32_t timer = 0;
float sens = 1;
void setup() {
  Wire.begin();
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  lastAB = (digitalRead(PIN_S1) << 1) | digitalRead(PIN_S2);
  pinMode(BTN_L, INPUT_PULLUP);
  pinMode(BTN_M, INPUT_PULLUP);
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_SENS, INPUT_PULLUP);
  Mouse.begin();
  Keyboard.begin();
}
void updateEncoder() { // Управляем колесом мыши
  uint8_t newAB = (digitalRead(PIN_S1) << 1) | digitalRead(PIN_S2);
  uint8_t idx   = (lastAB << 2) | newAB;
  int8_t  step  = encTable[idx & 0x0F];
  if (step) {
    accum += step;
    lastAB = newAB;
  }
  if (millis() - encLastMs > 10) {
    if (accum >= 2) { Mouse.move(0, 0, -1); accum = 0; encLastMs = millis(); }
    else if (accum <= -2) { Mouse.move(0, 0, 1); accum = 0; encLastMs = millis(); }
  }
}
void loop() {
  updateEncoder();
  if (millis() - timer > 60) {
    if (digitalRead(BTN_L) == LOW) Mouse.press(MOUSE_LEFT);   else Mouse.release(MOUSE_LEFT);
    if (digitalRead(BTN_M) == LOW) Mouse.press(MOUSE_MIDDLE); else Mouse.release(MOUSE_MIDDLE);
    if (digitalRead(BTN_R) == LOW) Mouse.press(MOUSE_RIGHT); else Mouse.release(MOUSE_RIGHT);
    if (digitalRead(BTN_SENS) == LOW && sens == 0.2){ // Меняем чувствительность мыши
      sens = 1;
      delay(150);}
    else if (digitalRead(BTN_SENS) == LOW && sens == 1) {
      sens = 0.2;
      delay(150);}
    timer = millis();
  }}