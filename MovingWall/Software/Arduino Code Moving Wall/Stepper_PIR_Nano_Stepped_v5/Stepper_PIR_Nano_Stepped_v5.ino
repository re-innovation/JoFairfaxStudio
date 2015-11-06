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
  A1  TrigPin
  A2  EchoPin
  
  A3  This is the input voltage with a 100k/10k divider.
 
  
  This code has the following functions:
  
  STEPPED:
  Each time the PIR is triggered then the motors will move one position forwards.
  When all positions are complete then the motor will be back to position 0
  There are 4096 (approx) steps 1 rotation (360degrees).
  There are four positions we can move to.
  The end position wil always be zero.
  
  The input voltage is monitored all the time.
  This is used to record the last position of the motor before shutting down.
  This means the unit can reset when powered up.

  
  
  This example code is in the public domain.
 */
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>

#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

#define trigPin A2  //  The connections for the ultrasonic distance sensor
#define echoPin A1 
#define voltageMonitor A3  // This is the pin to measure the voltage on the input


// ****************USER VARIABLES****************************************
// **********************************************************************

// ************** MODE ************************
// STEPPED =  stepps through 4 different locations

String mode = "STEPPED"; 

// ************** STEPPED INPUT ********************
// These are the three positions the unit will move into before returning to 0 in the fourth
// The positions are steps where 4096 = 360 degrees (approx)
int step1 = 1024;  
int step2 = 2048;
int step3 = -1024;

int previousStep = 0;  // A holder for the position the unit was left in.
                      // This means we can reset to zero when powered up.

// Ultrasonic distance sensor variables
int minDistance = 10;  // Minimum distance (cm) for the Ultrasonic Sensor
int maxDistance = 100;  // Maximum distance (cm) for the Ultrasonic Sensor

// Stepper motor variables
int maxSpeed = 800;  // The maximum speed for the motor (typical values 200-800)
int acceleration = 100;  // Acceleration of the motor (typical values (50 - 400)

// ********************* END OF USER VARIABLES***************************
// **********************************************************************

//int pir = 4; // PIR is connected to digital pin 4

int RESET = 2;  
int SW1 = 3;
int SW2 = 4;

int led = 13;  // LED on pin 13 - flash to make it obvious

boolean pirTriggered = LOW;  // This is a flag to stop things repeating

boolean stepTrigger =   LOW;  // This is to set off the step trigger

int stepCase = 0;  // This is the next step movement to do.
int modeCase = 0;  // This is the main mode to do.

// Varibales for writing to EEPROM
int hiByte;      // These are used to store longer variables into EEPROM
int loByte;


int sensorValue = 0;  // For the distance sensor
long duration, distance;// For the distance sensor
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  
  // Initialise the PIR as a input with a pull up resistor
  pinMode(RESET, INPUT_PULLUP); 
  pinMode(SW1, INPUT_PULLUP); 
  pinMode(SW2, INPUT_PULLUP);   

  pinMode(voltageMonitor, INPUT);
  
  pinMode(led,OUTPUT);  // Have the LED display an output
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  
  Serial.begin(115200);
  
  stepper1.setMaxSpeed(maxSpeed);  // usual value = 500
  stepper1.setSpeed(maxSpeed);  // usual value = 200
  stepper1.setAcceleration(acceleration); // usual value = 100
  
  // Retrieve the setpoints from EEPROM
  hiByte = EEPROM.read(0);
  loByte = EEPROM.read(1);
  previousStep = (hiByte << 8)+loByte;  // Get the previous step value
  Serial.print("Previous Step was:");
  Serial.println(previousStep);
  
  // We want to move to zero again to start once more.
  stepper1.setCurrentPosition(previousStep);  
  
  stepper1.moveTo(0);
  while(stepper1.run())
  { 
//    // We want to read the voltage during every step
//    // If the voltage drops below a certain amount
//    // We want to store the voltage and stop the movement of the motor
//    if(analogRead(voltageMonitor)<=200)
//    {
//      // This means the voltage is around 10V on the input
//      previousStep = stepper1.currentPosition();  // Store the value to EEPROM
//      // Save this value before all the power fails
//      EEPROM.write(0, previousStep >> 8);    // Do this seperately
//      EEPROM.write(1, previousStep & 0xff); 
//      // Write it to serial for DEBUG
//      Serial.println("LOW VOLTAGE");
//      Serial.println(previousStep);
//      break;
//    }    
  }
  // Switch off the motors
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);       
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,LOW);

  
  if(mode=="STEPPED")
  {
    modeCase = 0;
  }    
  
  
}//--(end setup )---

void loop() {
  
  switch(modeCase)  {
    case 0:    
      if(stepTrigger==HIGH)
      {
        Serial.println("Button PRESSED!");
        Serial.println(stepper1.currentPosition());
        // do something different depending on the case: 
        switch (stepCase) {
          case 0:   
            // ******* STEPPED MODE ******************
            stepper1.moveTo(step1);
            while(stepper1.run())
            { 
              // We want to read the voltage during every step
              // If the voltage drops below a certain amount
              // We want to store the voltage and stop the movement of the motor
              if(analogRead(voltageMonitor)<=200)
              {
                // This means the voltage is around 10V on the input
                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
                // Save this value before all the power fails
                EEPROM.write(0, previousStep >> 8);    // Do this seperately
                EEPROM.write(1, previousStep & 0xff); 
                // Write it to serial for DEBUG
                Serial.println("LOW VOLTAGE");
                Serial.println(previousStep);
                break;
              }   
            }
            Serial.print("Moved to:");
            Serial.println(step1);
            break;
          case 1:   
            stepper1.moveTo(step2);
            while(stepper1.run())
            {
              Serial.println(stepper1.currentPosition());
              // This displays the current position all the time
              
              // We want to read the voltage during every step
              // If the voltage drops below a certain amount
              // We want to store the voltage and stop the movement of the motor
              if(analogRead(voltageMonitor)<=200)
              {
                // This means the voltage is around 10V on the input
                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
                // Save this value before all the power fails
                EEPROM.write(0, previousStep >> 8);    // Do this seperately
                EEPROM.write(1, previousStep & 0xff); 
                // Write it to serial for DEBUG
                Serial.println("LOW VOLTAGE");
                Serial.println(previousStep);
                break;
              }   
              
            } 
            Serial.print("Moved to:");
            Serial.println(step2);
            break;
          case 2:    
            stepper1.moveTo(step3);
            while(stepper1.run())
            {
              Serial.println(stepper1.currentPosition());
              // This displays the current position all the time
              
              // We want to read the voltage during every step
              // If the voltage drops below a certain amount
              // We want to store the voltage and stop the movement of the motor
              if(analogRead(voltageMonitor)<=200)
              {
                // This means the voltage is around 10V on the input
                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
                // Save this value before all the power fails
                EEPROM.write(0, previousStep >> 8);    // Do this seperately
                EEPROM.write(1, previousStep & 0xff); 
                // Write it to serial for DEBUG
                Serial.println("LOW VOLTAGE");
                Serial.println(previousStep);
                break;
              }    
            }  
            Serial.print("Moved to:");
            Serial.println(step3);
            break;
          case 3:    
             stepper1.moveTo(0);
            while(stepper1.run())
            {
              Serial.println(stepper1.currentPosition());
              // This displays the current position all the time

              // We want to read the voltage during every step
              // If the voltage drops below a certain amount
              // We want to store the voltage and stop the movement of the motor
              if(analogRead(voltageMonitor)<=200)
              {
                // This means the voltage is around 10V on the input
                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
                // Save this value before all the power fails
                EEPROM.write(0, previousStep >> 8);    // Do this seperately
                EEPROM.write(1, previousStep & 0xff); 
                // Write it to serial for DEBUG
                Serial.println("LOW VOLTAGE");
                Serial.println(previousStep);
                break;
              }           
            }  
            Serial.print("Moved to:");
            Serial.println("0");
            break;
        }
        // Switch off the motors
        digitalWrite(motorPin1,LOW);
        digitalWrite(motorPin2,LOW);       
        digitalWrite(motorPin3,LOW);
        digitalWrite(motorPin4,LOW);
        
        // Move to the next step
        stepCase++;
        if(stepCase>=4)
        {
            stepCase=0; // return to zero
        }
      }
      
      break;
      // ******** END OF STEEPED MODE *********************
  }
  
  
  
  // ********** SENSOR READS ************************************ //
  // This is always within the loop
  
//  //***** UltraSonic Distance Sensor **********//
//  // This sction of code reads the ultrasonic distance sensor delay
//  for(int i = 0; i<=5; i++)
//  {
//    digitalWrite(trigPin, LOW);  // Added this line
//    delayMicroseconds(2); // Added this line
//    digitalWrite(trigPin, HIGH);
//    delayMicroseconds(1000); // Added this line
//    digitalWrite(trigPin, LOW);
//    duration = pulseIn(echoPin, HIGH);
//    distance += (duration/2) / 29.1;
//    delay(2);
//  }
//  distance = distance/5;  // Averaging
//  
//  
//  if(distance<=maxDistance&&distance>=minDistance)
//  {
//    stepTrigger = HIGH;
//  }
//  else
//  {
//    stepTrigger = LOW;
//  }
//    Serial.print("Ultrasonic:");
//    Serial.print(distance);
//    Serial.println(" cm");  
  
  delay(100);
  
  // ********** TEST CODE********************
  // This is TEST CODE for triggering on SW1
  if(digitalRead(SW1)==LOW)
  {
    stepTrigger = HIGH;
  }
  else
  {
    stepTrigger = LOW;
  }    
  
  //Serial.println(analogRead(voltageMonitor));
  //***********END OF TEST ******************
  

   
}

