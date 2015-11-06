/*
  Stepper Motor Controller
  
  This runs a stepper motor (or motors) from an AdaFruit Trinket.
  I'm using the 28BYJ-48 stepper motor with driver
  This Motor has a Gear ratio of 64 , and Stride Angle 5.625°  
  so this motor has a 4096 Steps .
  
  
  This example code is in the public domain.
 */
 
 
#include <Stepper.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//int step1 = 0;
//int step2 = 1;
//int step3 = 2;
//int step4 = 3;

int pir = 4; 

Stepper myStepper = Stepper(64, 0, 1, 2, 3); 

// the setup routine runs once when you press reset:
void setup() {                
  // Initialise the PIR as a input with a pull up resistor
  pinMode(pir, INPUT_PULLUP); 
  // Initialise the stepper motor speed
  myStepper.setSpeed(400);
}

// the loop routine runs over and over again forever:
void loop() {
  
    myStepper.step(2048);
    delay(500);
    myStepper.step(-2048); 
    delay(500);  
    
//    if(digitalRead(pir)==HIGH)
//    {
//      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//    }
//    else
//    {
//      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//    }
//    delay(10);               // wait for a second
   
  
}
