/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>

/*
 * Local Libraries
 */

#include "word_reel.h"

/*
 * Defines and typedefs
 */

//#define DEBUG_COMMANDS
//#define DEBUG_DETECTORS

#define NUMBER_OF_REELS (1)

/*
 * Private Variables
 */

// ID for this unit.
static const char s_this_id[] = "00";

// Command buffer and current write index
static char s_serial_buffer[8];
static uint8_t s_serial_index = 0;

// Flag and parameters for next motor move
static bool s_command_ready = false;
static bool s_next_direction_is_forwards = false;
static bool s_next_motor = 0;

// Motors

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

/*
 * Private functions
 */

static int two_chars_to_int(char const * const pc)
{
	int result = 0;

	uint8_t c1 = pc[0] - '0';
	uint8_t c2 = pc[1] - '0';

	if ((c1 < 10) && (c2 < 10))
	{
		result = c1 * 10 + c2;
	}

	return result;
}

static bool id_matches(char const * const id1, char const * const id2)
{
	return ((id1[0] == id2[0]) && (id1[1] == id2[1]));
}

static void reset_buffer()
{
	s_serial_index = 0;
}

static void process_buffer(char const * const buffer)
{
	int motor = 0;

	// Skip processing if ID in buffer doesn't match
	if (!id_matches(s_this_id, &buffer[1])) { return; }

	#ifdef DEBUG_COMMANDS	
	Serial.print("Got command '");
	Serial.print(buffer);
	Serial.println("'");
	#endif

	// Try to get motor ID from buffer.
	motor = two_chars_to_int(&buffer[4]);
	if (motor == 0 || motor > NUMBER_OF_REELS)
	{
		#ifdef DEBUG_COMMANDS
		Serial.println("Bad motor number.");
		#endif

		return;
	}

	// Try to get direction from buffer.
	if ((buffer[6] != 'F') && (buffer[6] != 'B'))
	{
		#ifdef DEBUG_COMMANDS
		Serial.println("Bad direction.");
		#endif

		return;
	}

	// Switch from 1, 2, 3, 4 motor numbering to 0, 1, 2, 3...
	s_next_motor = motor - 1;
	s_next_direction_is_forwards = buffer[6] == 'F';
	
	#ifdef DEBUG_COMMANDS
	Serial.print("Sending motor ");
	Serial.print(s_next_motor);
	Serial.println(s_next_direction_is_forwards ? " forwards" : " backwards.");
	#endif

	s_command_ready = true;
}

static void process_next_command()
{
	s_reels[s_next_motor].move_one_word(s_next_direction_is_forwards);
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

	int i;
	for (i = 0; i < NUMBER_OF_REELS; i++)
	{
		s_reels[i].initial_seek_to_word();
	}
}

void loop()
{
	if (s_command_ready)
	{
		process_next_command();
		s_command_ready = false;
	}

	run_motors();
	s_debug_task.tick();
}


void serialEvent()
{
	while (Serial.available())
	{
		char new_char = Serial.read();
		
		if (isspace(new_char)) { return; }

		// 'a' is the start of a new buffer
		if (new_char == 'a') { reset_buffer(); }

		s_serial_buffer[s_serial_index++] = new_char;

		// Transmitted commands are 7 chars in length
		if (s_serial_index == 7)
		{
			// Debug lines might use the buffer as a string, so null-terminate it;
			s_serial_buffer[7] = '\0';
			process_buffer(s_serial_buffer);
		}
	}
}
