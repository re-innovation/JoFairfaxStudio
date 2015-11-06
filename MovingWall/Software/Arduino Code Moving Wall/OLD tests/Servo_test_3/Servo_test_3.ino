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
 
#define led 13 // Pin 13 has an LED connected on most Arduino boards. 
 
#define trigPin 9  //  The connections for the ultrasonic distance sensor
#define echoPin 8 

#define PIR 3  // The PIR sensor is attached to pin D3

#define LDR A0  // A0 for the light dependant resistor 
 
#define averageOver 50

Servo myservo1;  // Creates a servo object
Servo myservo2;  // Creates a servo object
Servo myservo3;  // Creates a servo object

int PIRstate = LOW;

int LDRaverage = 0;
int distanceAverage[averageOver] = {0};

// the setup routine runs once when you press reset:
void setup() {       
  
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  

  pinMode(PIR,INPUT);  
  
  myservo1.attach(25);  // For the LDR
  myservo2.attach(26);  // For the PIR
  myservo3.attach(27);  // For the Ultrasonic
  
}

// the loop routine runs over and over again forever:
void loop() {

    
  //******* Light Dependant Positioning**********//
  // This sction of code reads the voltage from an LDR on pin A0
  // The reading is mapped to a position for a servo on pin D25
  // read the input on analog pin 0:
  int sensorValue = analogRead(LDR);
  sensorValue = map(sensorValue, 200, 900, 0, 179);
  
  LDRaverage = (LDRaverage + sensorValue)/2;  // This does a simple rolling average
  
  myservo1.write(LDRaverage);
  Serial.print("LDR Sensor:");
  Serial.println(LDRaverage); 
  

  //***** PIR Sensor **********//
  // This sction of code reads the digital output from a PIR sensor
  // The reading is mapped to a position for a servo on pin D26  
  PIRstate = digitalRead(PIR);
  if(PIRstate==HIGH)
  {
    // The PIR is activated, so move 180 degrees
    myservo2.write(180);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
    myservo2.write(0);
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
  
  //***** UltraSonic Distance Sensor **********//
  // This sction of code reads the ultrasonic distance sensor delay
  // The reading is mapped to a position for a servo on pin D27 
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  sensorValue = map(distance, 0, 30, 0, 179);
  for(int y = averageOver-2; y>=0; y--)
  {
    distanceAverage[y+1] = distanceAverage[y];  // This moves shifts all the old values up the array
  }
  distanceAverage[0] = sensorValue;  // Put the new value here
  
  // The calculate the average:
  for(int x = 0; x<averageOver; x++)
  {
    sensorValue = sensorValue+ distanceAverage[x];
  }
  sensorValue = sensorValue/averageOver;
  
  myservo3.write(sensorValue);  
 
  Serial.print("Ultrasonic:");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(20);               // wait for a second
  
}
