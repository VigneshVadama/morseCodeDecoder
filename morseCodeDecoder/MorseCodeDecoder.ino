#include <LiquidCrystal.h>
#define ledPin 13
#define ldr 3
int high = 1;
int low = 0;

int value = 0;
int buttonState = high;
int lastButtonState = low;
int blinking = false;
long previousMillis = 0;
long startTime ;
long elapsedTime ;
long breakTime = 0;
long finalTime = 0;
double gap;
double fractional;
double totalTime;
String getMorse[10];
String alphabet[6] = {"A","B","C","D","E","F"};
String morseDB[6] = {"-.",".---",".-.-",".--","-","--.-"};
int n=0;
LiquidCrystal lcd(8,9,10,11,12,13);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
/*  lcd.print("Insane Labs");
  delay(2000);
  lcd.clear();
  lcd.print("Morse Code Comm");
  delay(2000);
  lcd.clear(); */
  pinMode(ledPin, OUTPUT);
  pinMode(ldr,INPUT);
}

void loop() {
  getSignal();
}

void getSignal() {
  value = analogRead(ldr);
  if(value < 500) buttonState = low;
  else buttonState = high;
  if (buttonState == low && lastButtonState == high  &&  blinking == false) {
    startTime = millis();
    finalTime = millis() - breakTime;
    blinking = true;
    delay(5);
    lastButtonState = buttonState;
    digitalWrite(ledPin,HIGH);
  }
  else if (buttonState == high && lastButtonState == low && blinking == true) {
    elapsedTime =   millis() - startTime;
    blinking = false;
    lastButtonState = buttonState;
    digitalWrite(ledPin,LOW);
    time(elapsedTime);
  }
  else {
    if(blinking==true)
    breakTime = millis();
    lastButtonState = buttonState;
  }
  if(totalTime > 0.1) {
    if(totalTime < 0.3) {
      Serial.print("DIT ");
//      lcd.print("DIT ");
      totalTime = 0;
      getMorse[n]+=".";
    }
    else {
      Serial.print("DAH ");
//      lcd.print("DAH ");
      totalTime = 0;
      getMorse[n]+="-";

    }
  }
}

void time (long) {
  totalTime =  (int)(elapsedTime/1000L);
  gap = (int)(finalTime);
  fractional = (int)(elapsedTime % 1000L);
  totalTime += (fractional/1000);
  if(gap>250) {
    Serial.println();
    Serial.println(getMorse[n]);
    //lcd.print(alphabet[n]);
    if(getMorse[n]="-...") Serial.println("B");
    else if(getMorse[n]="-.") Serial.println("A");
    n++;
  }
  if(finalTime>1000) {
//    lcd.print(alphabet[n]);
//    Serial.println(getMorse[n]);
    n=0;
    for(int i=0;i<10;i++)
    getMorse[i] = "";
  }
}
