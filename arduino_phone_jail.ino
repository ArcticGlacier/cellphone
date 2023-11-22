#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPin = 6;
int redLEDPin = 8;
int greenLEDPin = 9;

int buttonState;
bool timerStarted = false;

unsigned long minutesLeft = 1; //ms
unsigned long secondsLeft = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(buttonPin, INPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(buttonPin, LOW);
  lcd.print("Press Button");
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH && !timerStarted){
    digitalWrite(greenLEDPin, LOW);  
    digitalWrite(redLEDPin, HIGH);
    timerStarted = true;
   	printLCD("JAIL TIME!",3,0);
    delay(1000);
  }
  else if(timerStarted){
   
    if(secondsLeft == 0 && minutesLeft > 0){
     minutesLeft -= 1;
     secondsLeft = 60;
    }
    secondsLeft -= 1;
    String secondsDisplayed = "";
    if(secondsLeft < 10){
      secondsDisplayed = "0" + String(secondsLeft);
    }
    else{
      secondsDisplayed = String(secondsLeft);
    }

    printLCD(String(minutesLeft) + ":" + secondsDisplayed, 6, 0);
    delay(1000);
  }
  if(timerStarted && minutesLeft == 0 && secondsLeft == 0){
    printLCD("Sentence Served!", 0, 0);
  	resetTimer();
  }
}

void printLCD(String msg, int cursorX, int cursorY){
    lcd.clear();
    lcd.setCursor(cursorX, cursorY);
    lcd.print(msg);
}

void resetTimer(){
   digitalWrite(greenLEDPin, HIGH);
   digitalWrite(redLEDPin, LOW);
   digitalWrite(buttonPin, LOW);
   minutesLeft = 1;
   secondsLeft = 0;
   delay(1000);
   lcd.clear();
   lcd.print("Press Button");
   timerStarted = false;
}