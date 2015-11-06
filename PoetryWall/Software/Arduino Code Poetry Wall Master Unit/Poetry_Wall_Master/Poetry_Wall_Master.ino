/*
  Poetry Wall Code: MASTER UNIT

  This runs a stepper motor (or motors) from an Arduino Nano
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
  A1  EchoPin
  A2  TrigPin

  A3  N/C

  A4  Photo Detector M1
  A5  Photo Detector M2
  A6  

  This code has the following functions:

  The code as a whole will
  MASTER UNIT:
  The MASTER unit will monitor the ultrasonic sensor.
  If detected then it will randomly choose 1,2,3 or 4 words to change.
  This will be from a random seed.
  The motors are called via serial line (at 9600 baud) using the format:
  aXXMYYD----
  Where XX is an ID for the slave unit, YY is the motor ID and D is the direction (F/B)


  This example code is in the public domain.
 */
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>

#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motor1Pin1  5     // IN1 on the ULN2003 driver 1
#define motor1Pin2  6     // IN2 on the ULN2003 driver 1
#define motor1Pin3  7     // IN3 on the ULN2003 driver 1
#define motor1Pin4  8     // IN4 on the ULN2003 driver 1

#define motor2Pin1  9     // IN1 on the ULN2003 driver 1
#define motor2Pin2  10     // IN2 on the ULN2003 driver 1
#define motor2Pin3  11     // IN3 on the ULN2003 driver 1
#define motor2Pin4  12     // IN4 on the ULN2003 driver 1

#define trigPin A2  //  The connections for the ultrasonic distance sensor
#define echoPin A1

//#define voltageMonitor A3  // This is the pin to measure the voltage on the input

#define photoSensor1 A4

// ****** Serial Data Read***********
// Variables for the serial data read
char inByte;         // incoming serial char
String str_buffer = "";  // This is the holder for the string which we will display
String data;        // Holds the various data from the Serial line

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int previousStep = 0;  // A holder for the position the unit was left in.
// This means we can reset to zero when powered up.

int RESET = 2;
int SW1 = 3;
int SW2 = 4;

int led = 13;  // LED on pin 13 - flash to make it obvious

boolean unitTrigger =   LOW;  // This is to set off the step trigger
//
//int stepCase = 0;  // This is the next step movement to do.
//int modeCase = 0;  // This is the main mode to do.

// Variables for writing to EEPROM
int hiByte;      // These are used to store longer variables into EEPROM
int loByte;

int motor1 = 0; // Holds the ID for Motor 1
int motor2 = 0; // Holds the ID for Motor 2
int motorID = 0;  // Holds the int for the motor to run

int sensorValue = 0;  // For the distance sensor
unsigned long duration, distance;// For the distance sensor

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

// ****************USER VARIABLES****************************************
// **********************************************************************

// Ultrasonic distance sensor variables
int minDistance = 20;  // Minimum distance (cm) for the Ultrasonic Sensor
int maxDistance = 80;  // Maximum distance (cm) for the Ultrasonic Sensor

// Stepper motor variables
int maxSpeed = 500;  // The maximum speed for the motor (typical values 200-800)
int acceleration = 100;  // Acceleration of the motor (typical values (50 - 400)


int wheelsToTrigger = 3;   // This is the number of wheels to trigger

int secondsToWait = 2;  // The seconds to wait before starting to check if its been triggered again
// ********************* END OF USER VARIABLES***************************
// **********************************************************************

long randNumber;  // This holds the random number
int randArray[12];  // Creates an int array for holding the random numbers

void setup() {

  // Initialise the DIO a input with a pull up resistor
  pinMode(RESET, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  pinMode(led, OUTPUT); // Have the LED display an output

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  randomSeed(analogRead(0));
  
  Serial.begin(9600);

  stepper1.setMaxSpeed(maxSpeed);  // usual value = 500
  stepper1.setSpeed(maxSpeed);  // usual value = 200
  stepper1.setAcceleration(acceleration); // usual value = 100

  stepper2.setMaxSpeed(maxSpeed);  // usual value = 500
  stepper2.setSpeed(maxSpeed);  // usual value = 200
  stepper2.setAcceleration(acceleration); // usual value = 100

  // Retrieve the setpoints from EEPROM
  motor1 = EEPROM.read(2);
  Serial.print("Motor1 ID:");
  Serial.println(motor1);
  motor2 = EEPROM.read(3);  
  Serial.print("Motor2 ID:");
  Serial.println(motor2);  
 
  switchOffMotors();

}//--(end setup )---

void loop() {

  
   //***** UltraSonic Distance Sensor **********//
  distance = 0; // Reset the distance value
  // This sction of code reads the ultrasonic distance sensor delay
  for(int i = 0; i<=10; i++)
  {
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 500000);
    distance += (duration/2) / 29.1;
    delay(2);
  }
  distance = distance/10;  // Averaging
  
  

  if((distance<=maxDistance&&distance>=minDistance)||digitalRead(SW1)==LOW)
  {
    unitTrigger = HIGH;
    Serial.println("TRIGGERED");
  }
  else
  {
    unitTrigger = LOW;
  }
  
  Serial.print("Ultrasonic:");
  Serial.print(distance);
  Serial.println(" cm");  

  // If the unit is triggered we need to randomly trigger 1,2,3,4... different motors
  if(unitTrigger ==HIGH)
  {
    // This means the unit has been triggered.

    //Lets create a random number array 
    for (int i=1;i<12;i++)
    {    
      // Here we want to check if its the same as any previous numbers
      bool same;
      do
      {
        same = false;
        randArray[i] = random(1, 13);
        for(int y=0;y<i;y++)
        {
          same = same || (randArray[y] == randArray[i]);
        }
      } while(same);
    
      Serial.print(randArray[i]);
      Serial.print(" ");
    }
    Serial.println("");
    // At this point we have an array of random numbers in which no two are the same.


    // Now we can call the motors required with a serial command.
    for(int i=0;i<=wheelsToTrigger;i++)
    {
      // First we clear the serial port
      inputString = "";
      Serial.flush();     
      
      // Here we ask each slave unit to switch on
      switch(randArray[i])
      {
        case 1:
          Serial.println("a00M01F-----");
        break;
        case 2:
          Serial.println("a00M02B-----");
        break;
        case 3:
          Serial.println("a01M01F-----");
        break;
        case 4:
          Serial.println("a01M02B-----");
        break;
        case 5:
          Serial.println("a02M01F-----");
        break;
        case 6:
          Serial.println("a02M02B-----");
        break;
        case 7:
          Serial.println("a03M01F-----");
        break;
        case 8:
          Serial.println("a03M02B-----");
        break;
        case 9:
          Serial.println("a04M01F-----");
        break;
        case 10:
          Serial.println("a04M02B-----");
        break;
        case 11:
          Serial.println("a05M01F-----");
        break;
        case 12:
          Serial.println("a05M02B-----");
        break;
      }
      
//      // Here we wait until "OK" is received by the unit
//      while(!Serial.available());
//      serialEvent();
    }
    delay(secondsToWait*1000); // a delay loop for slowing it all down
  }
  delay(500); // This is just a short loop delay
  
  // ********** TEST CODE********************
  // This is TEST CODE for triggering on SW1
  if(digitalRead(SW1)==LOW)
  {
    unitTrigger = HIGH;
  }
  else
  {
    unitTrigger = LOW;
  }
  //***********END OF TEST ******************

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() { 


  // Block until data available.
  if(Serial.available()>= 2){
    for (int i=0;i<2;i++)
    {
      inputString += (char)Serial.read();    
    }
    Serial.println(inputString); 
  }  
}

void switchOffMotors()
{
    // Switch off the motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin3, LOW);
  digitalWrite(motor1Pin4, LOW);
  // Switch off the motors
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
}




