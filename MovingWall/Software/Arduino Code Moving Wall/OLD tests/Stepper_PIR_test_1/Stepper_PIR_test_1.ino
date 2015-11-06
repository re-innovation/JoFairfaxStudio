/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
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

Stepper myStepper = Stepper(60, 0, 1, 2, 3); 
// the setup routine runs once when you press reset:
void setup() {                
//  // initialize the digital pin as an output.
//  pinMode(step1, OUTPUT);    
//  pinMode(step2, OUTPUT); 
//  pinMode(step3, OUTPUT); 
//  pinMode(step4, OUTPUT); 

  pinMode(pir, INPUT_PULLUP); 
  myStepper.setSpeed(100);
}

// the loop routine runs over and over again forever:
void loop() {
    myStepper.step(500);
    delay(500);
////  if(digitalRead(pir)==HIGH)
////  {
////    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
////  }
////  else
////  {
////    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
////  }
////  delay(10);               // wait for a second
//  digitalWrite(step1, HIGH);
//  digitalWrite(step3, HIGH);
//  delay(1);
//  digitalWrite(step1, LOW);
//  digitalWrite(step3, LOW);
//  delay(1); 
//  
//  digitalWrite(step2, HIGH);
//  digitalWrite(step4, HIGH);
//  delay(1);
//  digitalWrite(step2, LOW);
//  digitalWrite(step4, LOW);
//  delay(1);      
  
}
