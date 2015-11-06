/*
  Stepper Motor Controller
  
  This runs a stepper motor (or motors) from an Arduino Pro
  5V ATMEGA328 16MHz (12MHz?)
  
  I'm using the 28BYJ-48 stepper motor with driver
  This Motor has a Gear ratio of 64 , and Stride Angle 5.625°  
  so this motor has a 4096 Steps .
  
  This example code is in the public domain.
 */
 
 
#include <Stepper.h>

int pir = 4; // PIR is connected to digital pin 4
int led = 13;  // LED on pin 13 - flash to make it obvious

// Stepper motor is connected to digital pins 0,1,2,3
// This relates to 0 = IN3, 1 = IN1, 2 = IN4, 3 = IN3
Stepper myStepper = Stepper(10, 5, 6, 7, 8);
// 1 revolution = 2048 steps
// 90 degrees = 512 steps

boolean pirTriggered = LOW;  // This is a flag to stop things repeating

// the setup routine runs once when you press reset:
void setup() {                
  // Initialise the PIR as a input with a pull up resistor
  pinMode(pir, INPUT_PULLUP); 
  // Initialise the stepper motor speed
  myStepper.setSpeed(100);
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  Serial.begin(9600);
  
}

// the loop routine runs over and over again forever:
void loop() {
   
    
//    if(digitalRead(pir)==HIGH&&pirTriggered==LOW)
//    {
//      myStepper.step(1048);
//      myStepper.step(-512);     
//      pirTriggered = HIGH;  // Stops this happening until PIR triggered again      
//
//    }
//    else if(digitalRead(pir)==LOW)
//    {
//      pirTriggered = LOW;  // Reset the trigger so it will work again.
//    }
//    delay(10);               // wait for a bit. Lets not rush.
      
      digitalWrite(led,HIGH);
      Serial.println("Stepper forward");
      myStepper.step(512);
      delay(1000);
      
      digitalWrite(led,LOW);
      Serial.println("Stepper backward");
      myStepper.step(-512);  
      delay(1000);
}
