  //*********************************************//
  //**** Moving Wall Prototype ******************//
  // By Matt Little (matt@re-innovation.co.uk    //
  // For Jo Fairfax Studio                       //  
  // 22/12/14                                    //
  //*********************************************//
/*  
  Code for Arduino MEGA 2560 or MEGA ADK
  
  Uses 25 Servos Attached to pins D25 to D50
  
  An ultra sonic distance sensor is used on pins 8&9
  
  
  This example code is in the public domain.
 */
 
#include <Servo.h>
 
#define trigPin 9
#define echoPin 8 

#define PIR 3  // The PIR sensor is attached to pin D3
 
#define led 13 // Pin 13 has an LED connected on most Arduino boards.
 
Servo myservo1;  // Creates a servo object
Servo myservo2;  // Creates a servo object

int n = 0; 
int PIRstate = LOW;

// the setup routine runs once when you press reset:
void setup() {       
  
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  

  pinMode(PIR,INPUT);  
  
  myservo1.attach(25);
  myservo2.attach(26);  
}

// the loop routine runs over and over again forever:
void loop() {

   // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
 
  sensorValue = map(sensorValue, 200, 900, 0, 179);
  myservo1.write(sensorValue);
  Serial.println(sensorValue); 
  
  PIRstate = digitalRead(PIR);
  if(PIRstate==HIGH)
  {
    n=180;
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
    n=0;
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
  myservo2.write(n);
  
  delay(10);               // wait for a second
  
}
