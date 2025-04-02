#include <TaskScheduler.h>
int val; // показания фоторезистора
int lucs; // освещённость в люксах
boolean recivedFlag = false; // флаг получения данных
String photoData;
String strData;

//прототип функции sendData
void sendData();
void calculationToLucs();

Scheduler user_Scheduler;
Task taskSend(TASK_MILLISECOND * 3000, TASK_FOREVER, &sendData);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
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
  val = analogRead(A0); // находим показания фоторезистора
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
  calculationToLucs();
 // photoData = recieveData(); 
 // if (photoData != ""){
   // val = photoData.toInt();
  //Serial.println(lucs); // вывод люксов
  //delay(2000);
   }

void sendData(){
  Serial.println(lucs);
}