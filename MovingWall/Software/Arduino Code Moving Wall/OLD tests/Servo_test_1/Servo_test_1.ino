/*
  Code for Arduino MEGA 
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#include <Servo.h>
 
Servo myservo;  // Creates a servo object

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int n = 0; 

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  
  myservo.attach(2);
  
}

// the loop routine runs over and over again forever:
void loop() {

  myservo.write(n);
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);       // wait for a second  
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second
  
  n= n+10;
  
  if(n>180)
  {
    n=0;
  }
}
