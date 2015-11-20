/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>

/*
 * Local Libraries
 */

#include "slave_config.h"
#include "word_reel.h"
#include "commands.h"

/*
 * Defines and typedefs
 */

//#define DEBUG_COMMANDS
//#define DEBUG_DETECTORS

/*
 * Private Variables
 */

static WordReel s_reels[NUMBER_OF_REELS] = {
	WordReel(5, 7, 6, 8, A4, 1)
};

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

static void process_next_command()
{
	int motor = command_get_motor();
	bool fowards = command_get_direction();

	s_reels[motor].move_one_word(fowards);
}

static void run_motors()
{
	uint8_t i;
	
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].update_detector();
		s_reels[i].run();
	}
}

/*
 * Arduino functions
 */

void setup()
{
	Serial.begin(115200);

	// Move all reels to initial positions
	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].initial_seek_to_word();
	}
}

void loop()
{
	if (command_is_ready())
	{
		process_next_command();
		clear_command_ready_flag();
	}

	run_motors();
	s_debug_task.tick();
}

/* Read from serial in into the command processor */
void serialEvent()
{
	while (Serial.available())
	{
		char new_char = Serial.read();
		command_add_char(new_char);
	}
}
