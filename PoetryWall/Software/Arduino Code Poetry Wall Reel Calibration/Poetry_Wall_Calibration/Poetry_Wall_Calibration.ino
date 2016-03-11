#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>

#include <AccelStepper.h>
#include <SoftwareSerial.h>

#include "debug_config.h"
#include "word_reel.h"

#define NUMBER_OF_REELS (2)
#define LED_PIN (13)

static WordReel s_reels[NUMBER_OF_REELS] = {
  WordReel(
    5, 7, 6, 8,               // Motor pins
    A4,                       // Detector pin
    0,                        // Motor ID
    0,0,                  // Forward and backward steps to centre word at setup
    0,0,                  // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_move_complete_motor1), // Function to call when move is complete
  WordReel(
    9, 11, 10, 12,            // Motor pins
    A5,                       // Detector pin
    1,                        // Motor ID
    0,0,                  // Forward and backward steps to centre word at setup
    0,0,                  // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_move_complete_motor2), // Function to call when move is complete
};

static void on_move_complete_motor1()
{
    s_reels[0].off();
}

static void on_move_complete_motor2()
{
    s_reels[1].off();
}

void setup() {
  pinMode(LED_PIN, OUTPUT); // Have the LED display an output
  
  Serial.begin(9600);
  Serial.setTimeout(10000000000UL);
}

void loop() {
	
  if (Serial.available())
	{
		char c = Serial.read();
		if (c >= '0' and c <= '9')
		{
			int reel = c - '0';
			if (reel < NUMBER_OF_REELS)
			{
				s_reels[reel].run_interactive_calibration();
			}
		}
	}

}
