/* 
 * Stepper-IR-Tester

 * Simple utility to print out values from the reflective IR
 * sensor through a single rotation of the spool.
 *
 */

#include <AccelStepper.h>

#define STEPS_PER_REV (6230L)

static AccelStepper s_motor = AccelStepper(8, 5, 7, 6, 8);

static void print_detector()
{
	Serial.println(analogRead(A5));
}
void setup()
{
	Serial.begin(115200);

	delay(3000);
	
	long currentPosition = s_motor.currentPosition();

	s_motor.setMaxSpeed(500);
	s_motor.setSpeed(200);

	while (currentPosition < STEPS_PER_REV)
	{
		while( s_motor.currentPosition() == currentPosition)
		{ 
			s_motor.runSpeed();
		}
		print_detector();
		currentPosition = s_motor.currentPosition();
	}
}

void loop() {}
