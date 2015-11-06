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

int pir = A0; // PIR is connected to digital pin 4
int led = 13;  // LED on pin 13 - flash to make it obvious

boolean pirTriggered = LOW;  // This is a flag to stop things repeating

unsigned long int  newPosition = 0;  // Holds the new position to move to.

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  
  // Initialise the PIR as a input with a pull up resistor
  pinMode(pir, INPUT_PULLUP); 
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(500.0);
  stepper1.setSpeed(200);
  stepper1.setAcceleration(200.0);
}//--(end setup )---

void loop() {

    if(digitalRead(pir)==HIGH&&pirTriggered==LOW)
    {
      digitalWrite(led,HIGH);
      Serial.println("PIR Triggered");
 
//      stepper1.runToNewPosition(50);
//      stepper1.runToNewPosition(100);  
      newPosition = newPosition + 512;  // Add on 90 degrees.
      stepper1.runToNewPosition(newPosition);
     delay(1000); 
    }
    else if(digitalRead(pir)==LOW)
    {
//      stepper1.runToNewPosition(newPosition);  
//      stepper1.runToNewPosition(0);
      digitalWrite(led,LOW);
      pirTriggered = LOW;  // Reset the trigger so it will work again.
    }
    delay(10);               // wait for a bit. Lets not rush.
}

