/*
  Stepper Motor Controller
  
  This runs a stepper motor (or motors) from an Arduino Pro
  5V ATMEGA328 16MHz (12MHz?)
  
  I'm using the 28BYJ-48 stepper motor with driver
  This Motor has a Gear ratio of 64 , and Stride Angle 5.625°  
  so this motor has a 4096 Steps .
  
  Lots more info here:
  http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/
  
  Gear ratio is: 64 approx :1
  Actual gear ratio: 63.68395 : 1
  
  
  This example code is in the public domain.
 */
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

int pir = 4; // PIR is connected to digital pin 4
int led = 13;  // LED on pin 13 - flash to make it obvious

boolean pirTriggered = LOW;  // This is a flag to stop things repeating


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  
  // Initialise the PIR as a input with a pull up resistor
  pinMode(pir, INPUT_PULLUP); 
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(500.0);
  stepper1.setSpeed(200);
  stepper1.setAcceleration(100.0);
}//--(end setup )---

void loop() {
//  stepper1.setSpeed(50);
//  stepper1.runSpeed();
//  delay(1000);
//  stepper1.setSpeed(200);
//  stepper1.runSpeed();
//  delay(1000); 

    stepper1.runToNewPosition(0);
    stepper1.runToNewPosition(2048);
//    stepper1.runToNewPosition(100);
//    stepper1.runToNewPosition(120);  
    
//  stepper1.setSpeed(200);              
//  digitalWrite(led,HIGH);
//  Serial.println("Stepper forward");
//  // Initialise the stepper motor speed
//  stepper1.runSpeed();
//  delay(1000);
//  stepper1.setSpeed(50);  
//  digitalWrite(led,LOW);
//  Serial.println("Stepper backward"); 
//  stepper1.runSpeed();
//  delay(1000);
  
}

