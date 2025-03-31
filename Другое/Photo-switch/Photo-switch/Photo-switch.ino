#include <taskscheduler.h>
int val; // показания фоторезистора
int lucs; // освещённость в люксах
boolean recivedFlag = false; // флаг получения данных
String photoData;
String strData;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

String recieveData(){ // приём данных с COM-порта
  if (Serial.available() > 0){
    strData = "";
    while (Serial.available() > 0){
      strData += char(Serial.read());
    }
    recivedFlag = true;
  }
  if (recivedFlag){
    recivedFlag = false;
    return strData;
  }
  else return "";
}

void loop() {
 // photoData = recieveData(); 
  val = analogRead(A0); // находим показания фоторезистора
 // if (photoData != ""){
   // val = photoData.toInt();
  switch(val){ // перевод показаний фоторезистора в люксы
    case 0 ... 340:
      lucs = map(val, 0, 340, 1350, 300);
      break;
    case 341 ... 500:
      lucs = map(val, 340, 500, 300, 110);
      break;
    case 501 ... 1023:
      lucs = map(val, 500, 1023, 110, 0);
      break;
  }
  Serial.println(lucs); // вывод люксов
  delay(2000);
   }
