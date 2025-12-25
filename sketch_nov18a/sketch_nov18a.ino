#define ENCODER_CLK A0
#define ENCODER_DT  A1
#define BUTTON_PIN1 2

const int ledPins[] = {11, 10, 9, 6, 5, 3};
int lastClk = HIGH;
int brightness = map(analogRead(A3), 0, 1024, 0, 256);
int activeLed = 3;
int ledCount = 6;
int state = 0;
bool ledState = false;
const long interval = 1000;
unsigned long previousMillis = 0;
const unsigned long debounceDelay = 50;
unsigned long lastButtonPress = 0;


void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  for (int i = 0; i < 6; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  start();
}

void loop() {
  brightness = map(analogRead(A3), 0, 1024, 51, 256);
  digitalWrite(ledPins[activeLed], brightness);
  Serial.println(analogRead(A3));
}

void forxx(){ //цикл светодиода слева-направо
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    analogWrite(ledPins[activeLed], HIGH);
    analogWrite(ledPins[activeLed] - 1, LOW);
    if (activeLed == 5){
      activeLed = 0;
    }
  }
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

void start(){ //функция первичного теста работоспособности
  for (int i = 0; i < 6; i++){
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i - 1], LOW);
    delay(1000);
  }
  digitalWrite(ledPins[5], LOW);
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
  int buttonState = digitalRead(BUTTON_PIN1);
  unsigned long currentTime = millis();
  if (buttonState == HIGH && (currentTime - lastButtonPress) > debounceDelay) {
    lastButtonPress = currentTime;
    if (state == 0) {
      state = 1;
    } else {
      state = 0; 
    }
    while(digitalRead(BUTTON_PIN1) == HIGH) {
      delay(20);
    }
  }
}