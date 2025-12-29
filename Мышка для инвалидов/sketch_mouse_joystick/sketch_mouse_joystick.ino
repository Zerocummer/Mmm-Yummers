 #include <Wire.h>
 #include <MPU6050_light.h>
 #include <Mouse.h>
 #include <Keyboard.h>
 MPU6050 mpu(Wire);
 unsigned long timer = 0;
 #define ENC_A 3
 #define ENC_B 4
 bool p0, p1;
 int Xang, Yang, Zang;
 int linkerknop = 7;
 int middenknop = 8;
 int rechterknop = 9;
 void setup() {
  pinMode(linkerknop, INPUT_PULLUP);
  pinMode(middenknop, INPUT_PULLUP);
  pinMode(rechterknop, INPUT_PULLUP);
  Serial.begin(115200);
  Wire.begin();
  byte status = mpu.begin();
  while (status != 0) { } 
  delay(1000);
  mpu.calcOffsets(); 
  Mouse.begin();    
  Keyboard.begin(); 
 }
 void loop() {
 mpu.update();
 if ((millis() - timer) > 60) { 
  //чтение данных с гироскопа
  Xang=mpu.getAngleX();
  Yang=mpu.getAngleY();
  Zang=mpu.getAngleZ();
  
  int liknopstate = digitalRead(linkerknop);
  int miknopstate = digitalRead(middenknop);
  int reknopstate = digitalRead(rechterknop);
  bool vlagli = 0;
  bool vlagmi = 0;
  bool vlagre = 0;
    if ( liknopstate > 0){
    if (vlagli = 1){
    Mouse.release(MOUSE_LEFT);
    vlagli = 0;
    }
    }
  else {
    Mouse.press(MOUSE_LEFT);
    vlagli = 1;
    } 
    
  if ( miknopstate > 0){
    if (vlagmi = 1){
    Mouse.release(MOUSE_MIDDLE);
    vlagmi = 0;
    }
    }
  else {
    Mouse.press(MOUSE_MIDDLE);
    vlagmi = 1;
    }
   if ( reknopstate > 0){
   if (vlagre = 1){
    Mouse.release(MOUSE_RIGHT);
    vlagre = 0;
    }
    }
  else {
    Mouse.press(MOUSE_RIGHT);
    vlagre = 1;
    }   
   if ((Yang > 6) || (Yang < -6) || (Xang > 6) || (Xang < -6)){  
     if (Yang > 6){
     Yang = map(Yang, 6, 10, 1, 10);
     }
     else if (Yang < -6) {
     Yang = map(Yang, -10, -6, -10, -1); 
     }
     else if (Xang > 6) {  
     Xang = map(Xang, 6, 10, 1, 10); 
     }
     else if (Xang < -6) {
     Xang = map(Xang, -10, -6, -10, -1); 
     }
     Mouse.move(Yang, Xang, 0);
     pollEnc(digitalRead(ENC_A), digitalRead(ENC_B));
   }
  timer = millis();
   }}
void pollEnc(bool e0, bool e1) {
    if (p0 ^ p1 ^ e0 ^ e1) {
        if (p1 ^ e0){
        Mouse.move(0, 0, 6);
        }
        else{
          Mouse.move(0, 0, -6);
        }    // направление
        p0 = e0;
        p1 = e1;
    }
}