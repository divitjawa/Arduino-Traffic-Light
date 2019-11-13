#include <LiquidCrystal.h>
LiquidCrystal MyLCD(10, 6, 3, 4, 7, 2);

int danger;
boolean flag = true;
int redPin = 5;
int greenPin = 9;
int bluePin = 11;
int redDuration;
int greenDuration;
int ans;
 
#define COMMON_ANODE
 
void setup()
{
  Serial.begin(9600);
  MyLCD.begin(16, 2);
  MyLCD.home();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  Serial.println("Emergency? ('1' = yes/ '0' = no)");
  while(Serial.available() == 0){
  setColor(0, 55, 0); 
    }
  danger = Serial.parseInt();
  if(danger == 0) {
    Serial.println("WARNING: The following question will be asked only once.");
    Serial.println("Would you like to enter the duration for red & green light every time? ('1' = yes/ '0' = once only)");
    while(Serial.available() == 0){
    setColor(55, 0, 0); 
      }
    ans = Serial.parseInt();    
  }
}
 
void loop()
{
if(danger == 0) {
  if(flag) {    
    for(int i = 0; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
      MyLCD.setCursor(i, 1);
      MyLCD.print(" ");
    }  
    Serial.println("How long, in seconds, would you like the red light to be on? ");
    while(Serial.available() == 0) {
    setColor(55, 0, 0); 
      }
    redDuration = Serial.parseInt();
    Serial.println("How long, in seconds, would you like the green light to be on? ");
    Serial.println("");
    while(Serial.available() == 0) {
     setColor(55, 0, 0);
      }
    greenDuration = Serial.parseInt();
  }
  
  for(int i = 1; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
    }
    
    for(int i = redDuration; i > 0; i--) {
      for(int i = 1; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
      MyLCD.setCursor(i, 1);
      MyLCD.print(" ");
    }
      setColor(155, 0, 0);
      MyLCD.home();
      MyLCD.print("STOP: ");
      MyLCD.print(i);
      delay(1000);  
    }
    for(int i = 0; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
      MyLCD.setCursor(i, 1);
      MyLCD.print(" ");
    }  
  
    for(int i = greenDuration; i > 0; i--) {
      for(int i = 1; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
      MyLCD.setCursor(i, 1);
      MyLCD.print(" ");
    }
      setColor(0, 55, 0);
      MyLCD.home();
      MyLCD.print("GO: ");
      MyLCD.print(i);
      delay(1000);  
    }

    for(int i = 4; i > 0; i--){
    setColor(0, 0, 55);  
    MyLCD.home();
    MyLCD.print("STOP IN: ");
    MyLCD.print(i);
    delay(1000);
}
  if(ans == 0){
      flag = false;
    }
    else  {
      flag = true;
    }
  }
  else {  
    for(int i = 0; i < 3; i++){
      setColor(255, 0, 0);
      delay(100);
      setColor(0, 0, 255);
      delay(100);
    }
    MyLCD.home();
    MyLCD.print("EMERGENCY! DRIVE");
    MyLCD.setCursor(0, 1);
    MyLCD.print("CAREFULLY!");
    setColor(255, 0, 0);
    delay(200);
    setColor(0, 0, 255);
    delay(200);
  }
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
