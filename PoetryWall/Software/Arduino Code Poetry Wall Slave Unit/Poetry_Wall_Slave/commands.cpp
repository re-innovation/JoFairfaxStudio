/*
 * commands.cpp
 * 
 * Processes commands of the form
 * aXXMYYD
 * where:
 * XX is a two-digit node ID
 * YY is a two-digit motor ID
 * D is the direction to move the motor in (either F or B)
 *
 */

#include <Arduino.h>

/*
 * Local Libraries
 */

#include "debug_config.h"
#include "slave_config.h"
#include "commands.h"

/*
 * Defines and typedefs
 */

/*
 * Local Variables
 */

// Command buffer and current write index
static char s_command_buffer[8];
static uint8_t s_command_index = 0;

static bool s_command_ready = false;
static int s_last_commanded_motor;
static bool s_last_commanded_direction_fwd;


// ID for this unit.
static const char s_this_id[] = SLAVE_UNIT_ID;

/*
 * Private functions
 */

static void reset_buffer()
{
	s_command_index = 0;
}

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

void process_buffer(char const * const buffer)
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
	s_last_commanded_motor = motor - 1;
	s_last_commanded_direction_fwd = buffer[6] == 'F';
	
	#ifdef DEBUG_COMMANDS
	Serial.print("Motor ");
	Serial.print(s_last_commanded_motor+1);
	Serial.print(": moving");
	Serial.println(s_last_commanded_direction_fwd ? " forwards" : " backwards.");
	#endif

	s_command_ready = true;
}

void command_add_char(char new_char)
{
	if (isspace(new_char)) { return; }

	// 'a' is the start of a new buffer
	if (new_char == 'a') { reset_buffer(); }

	s_command_buffer[s_command_index++] = new_char;

	// Transmitted commands are 7 chars in length
	if (s_command_index == 7)
	{
		// Debug lines might use the buffer as a string, so null-terminate it;
		s_command_buffer[7] = '\0';
		process_buffer(s_command_buffer);
	}
}

bool command_is_ready()
{
	return s_command_ready;
}

void clear_command_ready_flag()
{
	s_command_ready = false;
}

int command_get_motor()
{
	return s_last_commanded_motor;
}

bool command_get_direction()
{
	return s_last_commanded_direction_fwd;
}
