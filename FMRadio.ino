/*  Arduino FM Radio
 *  Author: Angie Bai
 *  Date: January 19th, 2024
 *  Description: FM Radio of frequency 88.0 to 108.0 with stereo audio, volume control, 
 *  and a tuning function using a rotary encoder and a liquid crystal display.
 */

#include <LiquidCrystal.h> 
#include <Wire.h> 
#include <TEA5767Radio.h> 

//declare radio and set frequency default and boundaries
TEA5767Radio radio = TEA5767Radio(); 
float station = 99.1;
float prevStation = 99.1;
unsigned long last_run = 0;

//declare variables for display
const int RS=8, EN=9, D4=10, D5=11, D6=12, D7=13;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

//declare variables for rotary encoder
int pinCLK = 3; //interruptable pin
int pinDT = 4;
int pinSW = 5;

void setup() {
  Wire.begin();
  //set up display
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  //set default radio frequency
  radio.setFrequency(station);
  //set pin modes for rotary encoder
  attachInterrupt(digitalPinToInterrupt(pinCLK), shaft_moved, LOW);
  pinMode(pinDT, INPUT);   
  pinMode(pinSW, INPUT_PULLUP);
}

//rotary encoder
void shaft_moved(){
  if(millis()-last_run>5){
    //counter-clockwise
    if (digitalRead(pinDT) == 1){
      station = station - 0.1;
      if (station < 88.0) {
        station = 108.0;
      }                   
    }
    //clockwise
    if (digitalRead(pinDT) == 0){
      station = station + 0.1;
      if (station > 108.0) {
        station = 88.0;
      } 
    }
  }
  last_run = millis();
}

void loop() {
  //set new frequency only when the station has been changed (prevents background clicking noise that occurs when frequency is set)
  if (prevStation != station){
    radio.setFrequency(station);
  }
  prevStation = station;

  //display current radio station
  lcd.setCursor(0,0);
  lcd.print("Station: ");
  lcd.print(station);

  //adjust display depending on length of values printed
  if(station > 99.9 ){
  lcd.setCursor(14,0);
  lcd.print("FM");
  }
  else{
  lcd.setCursor(13,0);
  lcd.print("FM ");

  }
}
