/*
  Stepper Motor Controller

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





  SLAVE UNIT:
  This will receive a serial message (at 9600 baud).
  The message will be:
  aM??---------
  Where ?? is a number from 1-12
  When called, that motor (if the IDs match) will move forwards/backwards one word
  aSM1??-------
  aSM2??-------
  This will set the number of the motors and store this value into EERPOM.


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
#define voltageMonitor A3  // This is the pin to measure the voltage on the input
#define photoSensor1 A4

// ****** Serial Data Read***********
// Variables for the serial data read
char inByte;         // incoming serial char
String str_buffer = "";  // This is the holder for the string which we will display
String data;        // Holds the various data from the Serial line


int previousStep = 0;  // A holder for the position the unit was left in.
// This means we can reset to zero when powered up.


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

int motor1 = 0; // Holds the ID for Motor 1
int motor2 = 0; // Holds the ID for Motor 2
int motorID = 0;  // Holds the int for the motor to run

int sensorValue = 0;  // For the distance sensor
long duration, distance;// For the distance sensor

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

// ****************USER VARIABLES****************************************
// **********************************************************************

// Ultrasonic distance sensor variables
int minDistance = 10;  // Minimum distance (cm) for the Ultrasonic Sensor
int maxDistance = 100;  // Maximum distance (cm) for the Ultrasonic Sensor

// Stepper motor variables
int maxSpeed = 500;  // The maximum speed for the motor (typical values 200-800)
int acceleration = 100;  // Acceleration of the motor (typical values (50 - 400)

// ********************* END OF USER VARIABLES***************************
// **********************************************************************

void setup() {

  // Initialise the PIR as a input with a pull up resistor
  pinMode(RESET, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  pinMode(voltageMonitor, INPUT);

  pinMode(led, OUTPUT); // Have the LED display an output

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

  getData();
  sortData();
  delay(200);

  
  //
  //  switch(modeCase)  {
  //    case 0:
  //      if(stepTrigger==HIGH)
  //      {
  //        Serial.println("Button PRESSED!");
  //        Serial.println(stepper1.currentPosition());
  //        // do something different depending on the case:
  //        switch (stepCase) {
  //          case 0:
  //            // ******* STEPPED MODE ******************
  //            stepper1.moveTo(step1);
  //            while(stepper1.run())
  //            {
  //              // We want to read the voltage during every step
  //              // If the voltage drops below a certain amount
  //              // We want to store the voltage and stop the movement of the motor
  //              if(analogRead(voltageMonitor)<=200)
  //              {
  //                // This means the voltage is around 10V on the input
  //                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
  //                // Save this value before all the power fails
  //                EEPROM.write(0, previousStep >> 8);    // Do this seperately
  //                EEPROM.write(1, previousStep & 0xff);
  //                // Write it to serial for DEBUG
  //                Serial.println("LOW VOLTAGE");
  //                Serial.println(previousStep);
  //                break;
  //              }
  //            }
  //            Serial.print("Moved to:");
  //            Serial.println(step1);
  //            break;
  //          case 1:
  //            stepper1.moveTo(step2);
  //            while(stepper1.run())
  //            {
  //              Serial.println(stepper1.currentPosition());
  //              // This displays the current position all the time
  //
  //              // We want to read the voltage during every step
  //              // If the voltage drops below a certain amount
  //              // We want to store the voltage and stop the movement of the motor
  //              if(analogRead(voltageMonitor)<=200)
  //              {
  //                // This means the voltage is around 10V on the input
  //                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
  //                // Save this value before all the power fails
  //                EEPROM.write(0, previousStep >> 8);    // Do this seperately
  //                EEPROM.write(1, previousStep & 0xff);
  //                // Write it to serial for DEBUG
  //                Serial.println("LOW VOLTAGE");
  //                Serial.println(previousStep);
  //                break;
  //              }
  //
  //            }
  //            Serial.print("Moved to:");
  //            Serial.println(step2);
  //            break;
  //          case 2:
  //            stepper1.moveTo(step3);
  //            while(stepper1.run())
  //            {
  //              Serial.println(stepper1.currentPosition());
  //              // This displays the current position all the time
  //
  //              // We want to read the voltage during every step
  //              // If the voltage drops below a certain amount
  //              // We want to store the voltage and stop the movement of the motor
  //              if(analogRead(voltageMonitor)<=200)
  //              {
  //                // This means the voltage is around 10V on the input
  //                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
  //                // Save this value before all the power fails
  //                EEPROM.write(0, previousStep >> 8);    // Do this seperately
  //                EEPROM.write(1, previousStep & 0xff);
  //                // Write it to serial for DEBUG
  //                Serial.println("LOW VOLTAGE");
  //                Serial.println(previousStep);
  //                break;
  //              }
  //            }
  //            Serial.print("Moved to:");
  //            Serial.println(step3);
  //            break;
  //          case 3:
  //             stepper1.moveTo(0);
  //            while(stepper1.run())
  //            {
  //              Serial.println(stepper1.currentPosition());
  //              // This displays the current position all the time
  //
  //              // We want to read the voltage during every step
  //              // If the voltage drops below a certain amount
  //              // We want to store the voltage and stop the movement of the motor
  //              if(analogRead(voltageMonitor)<=200)
  //              {
  //                // This means the voltage is around 10V on the input
  //                previousStep = stepper1.currentPosition();  // Store the value to EEPROM
  //                // Save this value before all the power fails
  //                EEPROM.write(0, previousStep >> 8);    // Do this seperately
  //                EEPROM.write(1, previousStep & 0xff);
  //                // Write it to serial for DEBUG
  //                Serial.println("LOW VOLTAGE");
  //                Serial.println(previousStep);
  //                break;
  //              }
  //            }
  //            Serial.print("Moved to:");
  //            Serial.println("0");
  //            break;
  //        }
  //        // Switch off the motors
  //        digitalWrite(motorPin1,LOW);
  //        digitalWrite(motorPin2,LOW);
  //        digitalWrite(motorPin3,LOW);
  //        digitalWrite(motorPin4,LOW);
  //
  //        // Move to the next step
  //        stepCase++;
  //        if(stepCase>=4)
  //        {
  //            stepCase=0; // return to zero
  //        }
  //      }
  //
  //      break;
  //      // ******** END OF STEEPED MODE *********************
  //  }
  //
  //
  //
  //  // ********** SENSOR READS ************************************ //
  //  // This is always within the loop
  //
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
  //
  //  if((distance<=maxDistance&&distance>=minDistance)||digitalRead(SW1)==LOW)
  //  //if((distance<=maxDistance&&distance>=minDistance))
  //  {
  //    stepTrigger = HIGH;
  //  }
  //  else
  //  {
  //    stepTrigger = LOW;
  //  }
  //
  //  Serial.print("Ultrasonic:");
  //  Serial.print(distance);
  //  Serial.println(" cm");
  //
  //  // We want to read the voltage during every step
  //  // If the voltage drops below a certain amount
  //  // We want to store the voltage and stop the movement of the motor
  //  if(analogRead(voltageMonitor)<=200)
  //  {
  //    // This means the voltage is around 10V on the input
  //    previousStep = stepper1.currentPosition();  // Store the value to EEPROM
  //    // Save this value before all the power fails
  //    EEPROM.write(0, previousStep >> 8);    // Do this seperately
  //    EEPROM.write(1, previousStep & 0xff);
  //    // Write it to serial for DEBUG
  //    Serial.println("LOW VOLTAGE");
  //    Serial.println(previousStep);
  //  }
  //
  ////  // ********** TEST CODE********************
  ////  // This is TEST CODE for triggering on SW1
  ////  if(digitalRead(SW1)==LOW)
  ////  {
  ////    stepTrigger = HIGH;
  ////  }
  ////  else
  ////  {
  ////    stepTrigger = LOW;
  ////  }
  ////  //***********END OF TEST ******************
  //


}


// **********************GET DATA SUBROUTINE*****************************************
// This sub-routine picks up and serial string sent to the device and sorts out a power string if there is one
// All values are global, hence nothing is sent/returned

void getData()
{
  // **********GET DATA*******************************************
  // We want to find the bit of interesting data in the serial data stream
  // As mentioned above, we are using LLAP for the data.
  // All the data arrives as serial commands via the serial interface.
  // All data is in format aDDDDDDDDDDD
  if (Serial.available() > 0)
  {
    inByte = Serial.read(); // Read whatever is happening on the serial port

    if (inByte == 'a') // If we see an 'a' then read in the next 11 chars into a buffer.
    {
      str_buffer += inByte;
      for (int i = 0; i < 11; i++) // Read in the next 11 chars - this is the data
      {
        inByte = Serial.read();
        str_buffer += inByte;
      }
      //Serial.println(str_buffer);  // TEST - print the str_buffer data (if it has arrived)
      sortData();
      str_buffer = ""; // Reset the buffer to be filled again
    }
  }
}

// **********************SORT DATA SUBROUTINE*****************************************
// This sub-routine takes the read-in data string (12 char, starting with a) and does what is required with it
// The str-buffer is global so we do not need to send it to the routine

void sortData()
{
  // Here we read the data whoch has arrived and sort out voltage and power:

  // ****** POWER *********************
  // Receive Power Data in format “aXXP????-----“
  // Where XX is the reference and ???? is the data
  if (str_buffer.substring(1, 2) == "M")
  {
    data = str_buffer.substring(2,4);
    motorID = data.toInt();
    if(motorID==motor1)
    {
      stepper1.moveTo(stepper1.currentPosition()+550);
      while (stepper1.run())
      {
        if(analogRead(photoSensor1)>=700)
        {
          break;
        }
      }
      switchOffMotors();
    }
    if(motorID==motor2)
    {
      stepper2.moveTo(stepper2.currentPosition()-550);
      while (stepper2.run())
      {
        if(digitalRead(SW1)==LOW)
        {
          break;
        }        
      }
      switchOffMotors();
    }  
  }

  if (str_buffer.substring(1, 4) == "SM1")
  {
    data = str_buffer.substring(4,6);
    motor1 = data.toInt();
    Serial.print("Motor1 ID changed to:");
    Serial.println(motor1);   
    EEPROM.write(2, motor1);    // Write the beep flag to EEPROM
  }

  if (str_buffer.substring(1, 4) == "SM2")
  {
    data = str_buffer.substring(4,6);
    motor2 = data.toInt();
    Serial.print("Motor2 ID changed to:");
    Serial.println(motor2);   
    EEPROM.write(3, motor2);    // Write the beep flag to EEPROM
  }


  // ****** VOLTAGE ********************
  // Receive Power Data in format “aXXV???-----“
  // Where XX is the reference and ??? is the data
  else if (str_buffer.substring(3, 4) == "V")
  {
    //    Serial.print("Voltage:");
    //    Serial.println(str_buffer.substring(4,7));
    //writedataflag=HIGH;  // Set the unit to write the data
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




