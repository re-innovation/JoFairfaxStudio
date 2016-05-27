/*
 * Stepper_Poetry_Nano_Stepped_v4
 *
 * SLAVE Controller
 *
 * Receives commands over serial
 * 
 */

/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>
#include <SoftwareSerial.h>

/*
 * Local Libraries
 */

#include "debug_config.h"
#include "word_reel.h"
#include "commands.h"
#include "slave_config.h"

/*
 * Defines
 */

//#define SLAVE_UNIT_ID "00"
//
//#define NUMBER_OF_REELS (2)

#define CMD_RX_PIN (3)
#define CMD_TX_PIN (4)

/*
 * Private Variables
 */

static WordReel s_reels[NUMBER_OF_REELS] = {
	WordReel(
		5, 7, 6, 8,			// Motor pins
		A4,					// Detector pin
		1,					// Motor ID
		50, 240, 			// Forward and backward steps to centre word at setup
		30, 170, 			// Forward and backward steps to centre word when running
		false, 				// Invert fwd/back movement sense
		on_move_complete),	// Function to call when move is complete

	WordReel(
		9, 11, 12, 10,
		A5,
		2,
		150, 240,
		30, 70,
		false,
		on_move_complete)
};

static SoftwareSerial s_serial_cmd(CMD_RX_PIN, CMD_TX_PIN);

/*
 * Private Functions
 */

static void on_move_complete(void)
{
	s_serial_cmd.print("OK");
}

/* debug_task_fn: Prints any repeating debug strings */
static void debug_task_fn()
{
	#ifdef DEBUG_DETECTORS
	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		Serial.print(s_reels[i].detectorValue());
		Serial.println(s_reels[i].isTriggered() ? "(trig)" : "");
	}
	#endif
}
static TaskAction s_debug_task(debug_task_fn, 1000, INFINITE_TICKS);

/* process_any_pending_commands: If a command is pending, process it */
static void process_any_pending_commands()
{
	if (command_is_ready())
	{
		int motor = command_get_motor();
		bool forwards = command_get_direction();

		s_reels[motor].move_one_word(forwards);
		clear_command_ready_flag();
	}
}

/* run_motors: Run the motors while keeping IR detectors updated */
static void run_motors()
{
	uint8_t i;
	
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].update_detector();
		s_reels[i].run();
	}
}

/* read_command_from_serial: Poll software serial for incoming chars */
static void read_command_from_serial()
{
	while (s_serial_cmd.available())
	{
		char new_char = s_serial_cmd.read();
		command_add_char(new_char);
	}
}

/*
 * Arduino functions
 */

void setup()
{
	Serial.begin(9600);
	s_serial_cmd.begin(9600);

	// Move all reels to initial positions
	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].initial_seek_to_word();
	}
}

void loop()
{
	process_any_pending_commands();
	run_motors();
	read_command_from_serial();
	s_debug_task.tick();
}
