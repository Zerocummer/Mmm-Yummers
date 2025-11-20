#define ENCODER_CLK A0
#define ENCODER_DT  A1
#define BUTTON_PIN 4

const int ledPins[] = {3, 5, 6, 9, 10, 11};
int lastClk = HIGH;
int brightness = map(analogRead(A3), 0, 1024, 0, 256);
int activeLed = 0;
int ledCount = 6;
int state = 0;
bool ledState = false;
const long interval = 100;
unsigned long previousMillis = 0;
const unsigned long debounceDelay = 50;
unsigned long lastButtonPress = 0;


void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  for (int i = 0; i < 4; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  start();
}

void loop() {
  switch(state){
    case 0:
    checkButton();
    break;
    case 1:
    
    break;
  }
  /*encoderCheck();
  activeLed = (ledCount + activeLed) % ledCount;
  brightness = map(analogRead(A3), 0, 1024, 0, 256);*/
}

void updateLeds(){ //обновление актуальности светодиода
  for(int i = 0; i < ledCount; i++){
    if (i == activeLed){
      digitalWrite(ledPins[i], brightness);
    }
    else{
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void start(){ //функция старта
  for (int j = 0; j < 5; j++){
  for (int i = 0; i < ledCount; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(200);
  for (int i = 0; i < ledCount; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(200);
  }
}

void encoderCheck(){ //функция проверки энкодера и последующего действия в зависимости в какую сторону повернулся энкодер
  int newClk = digitalRead(ENCODER_CLK);
  if (newClk != lastClk) {
    lastClk = newClk;
    int dtValue = digitalRead(ENCODER_DT);
    if (newClk == LOW && dtValue == HIGH) {
      activeLed++;
    }
    if (newClk == LOW && dtValue == LOW) {
      activeLed --;
    }
  }
}

void blink(){ //моргание светодиодов
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    ledState = !ledState;
    for(int i = 0; i < ledCount; i++){
      if (i == activeLed){
        digitalWrite(ledPins[i], ledState ? brightness : 0);
      }
      else{
        digitalWrite(ledPins[i], LOW);
      }
  }
  }
}

void checkButton() { //читаем состояние кнопки
  int buttonState = digitalRead(BUTTON_PIN);
  unsigned long currentTime = millis();
  if (buttonState == HIGH && (currentTime - lastButtonPress) > debounceDelay) {
    lastButtonPress = currentTime;
    if (state == 0) {
      state = 1;
      updateLeds(); 
    } else {
      state = 0; 
    }
    while(digitalRead(BUTTON_PIN) == HIGH) {
      delay(10);
    }
  }
}