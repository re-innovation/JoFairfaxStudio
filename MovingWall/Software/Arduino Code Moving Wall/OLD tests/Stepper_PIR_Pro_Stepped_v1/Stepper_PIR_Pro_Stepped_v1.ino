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
  
  The PCB has the following wiring:
  
  Stepper Motor Set 1 (6 x motors) is on:
  D5,D6,D7,D8
  
  Stepper Motor Set 2 (6 x motors) is on:
  D9,D10,D11,D12
  
  Connectors K1/K2/K3/K4 decide if all 12 Motors do the same thing or
  if there are two sets of 6 motors which can do different things.
  
  INPUTS:
  RESET  D2
  SW1    D3
  SW2    D4
  
  DETECT_IN1
  A0
  A1
  A2
  
  DETECT_IN2
  A4
  A5
  A6
  
  This code has the following functions:
  
  STEPPED:
  Each time the PIR is triggered then the motors will move one position forwards.
  When all positions are complete then the motor will be back to position 0
  There are 4096 (approx) steps 1 rotation (360degrees).
  There are four positions we can move to.
  The end position wil always be zero.
  
  
  This example code is in the public domain.
 */
 
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

// ****************USER VARIABLES****************************************
// **********************************************************************

// ************** MODE ************************
// STEPPED =  stepps through 4 different locations

String mode = "STEPPED"; 

// ************** STEPPED INPUT ********************
// These are the three positions the unit will move into before returning to 0 in the fourth
// The positions are steps where 4096 = 360 degrees
int step1 = 1024;  
int step2 = 2048;
int step3 = -1024;


// ********************* END OF USER VARIABLES***************************
// **********************************************************************

//int pir = 4; // PIR is connected to digital pin 4

int RESET = 2;  
int SW1 = 3;
int SW2 = 4;

int led = 13;  // LED on pin 13 - flash to make it obvious

boolean pirTriggered = LOW;  // This is a flag to stop things repeating

int stepCase = 0;  // This is the next step movement to do.

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  
  // Initialise the PIR as a input with a pull up resistor
  pinMode(RESET, INPUT_PULLUP); 
  pinMode(SW1, INPUT_PULLUP); 
  pinMode(SW2, INPUT_PULLUP);   
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(500.0);
  stepper1.setSpeed(200);
  stepper1.setAcceleration(100.0);
  
  
  
}//--(end setup )---

void loop() {
  
  switch(mode)  {
    case "STEPPED":    
      if(digitalRead(SW1)==LOW)
      {
        Serial.println("Button PRESSED!");
    
        // do something different depending on the case: 
        switch (stepCase) {
          case 0:   
            stepper1.runToNewPosition(step1);
            Serial.print("Moved to:");
            Serial.println(step1);
            break;
          case 1:   
            stepper1.runToNewPosition(step2); 
            Serial.print("Moved to:");
            Serial.println(step2);
            break;
          case 2:    
            stepper1.runToNewPosition(step3);  
            Serial.print("Moved to:");
            Serial.println(step3);
            break;
          case 3:    
            stepper1.runToNewPosition(0);  
            Serial.print("Moved to:");
            Serial.println("0");
            break;
        }
             
        stepCase++;
        if(stepCase>=4)
        {
            stepCase=0; // return to zero
        }
      }
      delay(100);
      break;
  }

  
//  stepper1.setSpeed(50);
//  stepper1.runSpeed();
//  delay(1000);
//  stepper1.setSpeed(200);
//  stepper1.runSpeed();
//  delay(1000); 


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

  
}

