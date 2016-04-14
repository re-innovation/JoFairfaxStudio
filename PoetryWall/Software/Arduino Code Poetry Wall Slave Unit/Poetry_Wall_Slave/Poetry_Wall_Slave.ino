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
#include "slave_config.h"
#include "word_reel.h"
#include "commands.h"

/*
 * Defines
 */

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
		40,
		0, 0, 			// Forward and backward steps to centre word when running
		true, 				// Invert fwd/back movement sense
		on_move_complete_1),	// Function to call when move is complete
	WordReel(
		9, 11, 12, 10,
		A5,
		2,
		480,
		170, 50,
		false,
		on_move_complete_2)
};

static SoftwareSerial s_serial_cmd(CMD_RX_PIN, CMD_TX_PIN);

/*
 * Private Functions
 */

static void send_to_master(char const * str)
{
	pinMode(CMD_TX_PIN, OUTPUT);
	s_serial_cmd.print(str);
	pinMode(CMD_TX_PIN, INPUT);
}

static void on_move_complete_1(void)
{
	Serial.println("Motor 1: Move complete!");
	switch_off_motors();
	send_to_master("OK");
}

static void on_move_complete_2(void)
{
	Serial.println("Motor 2: Move complete!");
	switch_off_motors();
	send_to_master("OK");
}

/* debug_task_fn: Prints any repeating debug strings */
static void debug_task_fn()
{
	#ifdef DEBUG_DETECTORS
	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		Serial.print("Motor ");
		Serial.print(i+1);
		Serial.print(": ");
		Serial.print(s_reels[i].detectorValue());
		Serial.println(s_reels[i].isTriggered() ? "(trig)" : "");
	}
	#endif
}
static TaskAction s_debug_task(debug_task_fn, DEBUG_DETECTORS_PERIOD, INFINITE_TICKS);

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

	while (Serial.available())
	{
		char new_char = Serial.read();
		command_add_char(new_char);
	}
}

/* switch_off_motors: turns off all motor drives to save power */
void switch_off_motors()
{
  int i;
  for (i = 0; i < NUMBER_OF_REELS; i++)
  {
    s_reels[i].off();
  }
}


/*
 * Arduino functions
 */

void setup()
{
	Serial.begin(9600);
	s_serial_cmd.begin(9600);
	
	// Start serial TX pins as input to avoid contention
	pinMode(CMD_TX_PIN, INPUT);

	// Move all reels to initial positions
	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].initial_seek_to_word();
		s_reels[i].off();
	}
}

void loop()
{
	process_any_pending_commands();
	run_motors();
	read_command_from_serial();
	s_debug_task.tick();
}
