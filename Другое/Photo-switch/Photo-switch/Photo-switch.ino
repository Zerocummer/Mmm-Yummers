#include <TaskScheduler.h>
#include <Servo.h>
int val; // показания фоторезистора
int lucs; // освещённость в люксах
int maxIndex;
boolean recivedFlag = false; // флаг получения данных
String photoData;
String strData;
Servo myservo;
const int photoResistorPins[4] = {A0, A1, A2, A3};
int allValues[4];

//прототип функции sendData и calculationToLucs
void sendData();
void calculationToLucs();

Scheduler user_Scheduler;
Task taskSend(TASK_MILLISECOND * 3000, TASK_FOREVER, &sendData);

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  //Добавляем задание в обработчик
  user_Scheduler.addTask(taskSend);
  taskSend.enable();
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
void calculationToLucs(){
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
}
void loop() {
  user_Scheduler.execute();
  for (int i = 0; i < 4; i++) {
    allValues[i] = analogRead(photoResistorPins[i]);
  }

  int maxIndex = 0; // находим самый освещённый фоторезистор
  for (int i = 1; i < 4; i++) {
    if (allValues[i] > allValues[maxIndex]) {
      maxIndex = i;
    }
  }
  val = analogRead(photoResistorPins[maxIndex]);
  calculationToLucs();
  myservo.write(maxIndex * 90);
 // photoData = recieveData(); 
 // if (photoData != ""){
   // val = photoData.toInt();
  //Serial.println(lucs); // вывод люксов
  //delay(2000);
   }

void sendData(){
  Serial.println(lucs);
}