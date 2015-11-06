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

int turnsCounterTens = 0;  // Counts number of times we have rotated
int turnsCounterHundreds = 0;  // Counts number of times we have rotated
int turnsCounterThousands = 0;  // Counts number of times we have rotated
int turnsCounterTenThou = 0;  // Counts number of times we have rotated

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  
  // Initialise the PIR as a input with a pull up resistor
  pinMode(pir, INPUT_PULLUP); 
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(500.0);
  stepper1.setSpeed(500);
  stepper1.setAcceleration(200.0);
}//--(end setup )---

void loop() {
   // The position of the motor is set by the number of pulses to move it.
   // The Actual gear ratio: 63.68395 : 1
   // Each pulse will move it 5.625 degrees / 63.68395 = 0.011326807 degrees per step
   // 4048 steps = 357.5469 degrees.
   // 360 degrees = 360 x 63.68395 / 5.625 = 4075.7728 pulses
   
   // We can solve errors by counting exact pulses and every so often adjusting
   // 0.7728 x some number = whole number 
   // 0.7728 x 10000 = whole number
   // If we adjust every 10 rotations then we add on 7 steps
   // Also every 100 rotations we add on 7 steps
   // Every 1000 rotations we add on 2 steps
   // Every 10000 rotations we add on 8 steps
   
   // TESTING - RUN ALL THE TIME
   
//    if(digitalRead(pir)==HIGH&&pirTriggered==LOW)
    if(HIGH == HIGH)
    {
      digitalWrite(led,HIGH);
      Serial.println("PIR Triggered");
      stepper1.runToNewPosition(newPosition);  
     
      newPosition = newPosition + 4075;  // Add on 360 degrees.
      turnsCounterTens++;
      if(turnsCounterTens>=10)
      {
        newPosition = newPosition+7;  // Adjustment
        turnsCounterTens = 0;
        turnsCounterHundreds++;
        if(turnsCounterHundreds>=10)
        {
          newPosition = newPosition+7;  // Adjustment
          turnsCounterHundreds = 0;
          turnsCounterThousands++;
          if(turnsCounterHundreds>=10)
          {
            newPosition = newPosition+2;  // Adjustment
            turnsCounterThousands = 0;
            turnsCounterTenThou++;
            if(turnsCounterTenThou>=10)
            {
              newPosition = newPosition+8;  // Adjustment
              turnsCounterTenThou = 0;
            }          
          }          
        } 
      }
      Serial.print("Position is"); 
      Serial.println(newPosition);       
    }
    else if(digitalRead(pir)==LOW)
    {
      digitalWrite(led,LOW);
      pirTriggered = LOW;  // Reset the trigger so it will work again.
    }
    delay(5000);               // wait for a bit. Lets not rush.
}

