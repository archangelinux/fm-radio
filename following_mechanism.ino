#include "arduino_secrets.h"

#include <IRremote.hpp>

#include <Servo.h>
#include <NewPing.h>

int recvPin = 8;
IRrecv recv(recvPin);
decode_results results;
unsigned long key_val = 0;

bool ultrasonicOn = false;

void setup() {
recv.enableIRIn();

}

void loop() {
  if (receiver.decode($results)){
    if (results.value == 0XFFFFFFF){
      results.value = key_val;
    }
    switch(results.value){
      case 0xFF18E7: //2
        driveForward();
        break;
       case 0xFF10EF: //4
       turnLeft();
            break ; 
      case 0xFF38C7: //5
       driveStop();
            break ;
      case 0xFF5AA5: //6
       turnRight();
      case 0xFF4AB5: //8
       driveReverse();
        break;
      case 0XFF6897: //0
        ultrasonicOn = !untrasonicOn;
        break;
      
    }
    key_val = results.value;
    recv.resume();
  }

void driveForward(){
}
void turnLeft(){
}
void driveStop(){
}
void turnRight(){
}
void driveReverse(){
}

/*while(irrecv.decode(&results)){
    irrecv.resume();
    delay(150);*/
}
}