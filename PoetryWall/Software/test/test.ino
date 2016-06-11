/*
 * Stepper_Poetry_Nano_Stepped_v4
 *
 * test.ino
 * 
 * Small sketch for quickly testing small bits of functionality
 */

/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>
#include <SoftwareSerial.h>


/*
 * Arduino functions
 */

#define STEPS_PER_REV (6245L)

#define NUMBER_OF_WORDS (10L)

#define STEPS_PER_WORD (STEPS_PER_REV / NUMBER_OF_WORDS)
#define STEPS_PER_DIVISION (STEPS_PER_WORD/2)

//static const int detector_pin = A4;
static const int detector_pin = A5;

//static AccelStepper m_motor(8, 9, 11, 12, 10);
static AccelStepper m_motor(8, 5, 7, 6, 8);

void setup()
{
	Serial.begin(9600);
	pinMode(detector_pin, INPUT);
	m_motor.setAcceleration(100);
	m_motor.setMaxSpeed(1000);
	m_motor.setSpeed(1000);
	m_motor.moveTo(STEPS_PER_REV*10L);
}

void loop()
{
	m_motor.run();
//	Serial.println(analogRead(detector_pin));
//	delay(250);
}
