/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>

/*
 * Defines and typedefs
 */

#define DEBUG_MOTORS
#define DEBUG_COMMANDS
#define DEBUG_DETECTORS

#define NUMBER_OF_MOTORS (1)

/* 
 * STEPS_PER_WORD is the ideal number of steps to move between words
 * When the detector finds the actual word, STEPS_TO_STOP is
 * the number of steps that should be moved before stop.
 */
#define STEPS_PER_WORD (1200L)
#define STEPS_TO_STOP_FORWARD (100L)
#define STEPS_TO_STOP_BACKWARD (200L)

enum move_state
{
	MS_STOPPED_DETECTOR,
	MS_STOPPED_MOTOR,
	MS_MOVING_AWAY_FROM_OLD_POSITION,
	MS_MOVING_TO_NEW_POSITION
};
typedef enum move_state MOVE_STATE;

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

static AccelStepper s_motors[NUMBER_OF_MOTORS] = {
	AccelStepper(8, 5, 7, 6, 8),
	//AccelStepper(8, 9, 11, 10, 12)
};

static MOVE_STATE s_move_state[NUMBER_OF_MOTORS] = {
	MS_STOPPED_MOTOR,
	//MS_STOPPED_MOTOR
};

/*
 * Photodetectors
 */

static bool s_reel_detector_triggered[NUMBER_OF_MOTORS] = {
	false,
	//false,
};

static uint8_t s_detector_pins[NUMBER_OF_MOTORS] = {
	A4,
	//A5
};

static uint32_t s_detector_average[NUMBER_OF_MOTORS];

static void debug_task_fn()
{
	#ifdef DEBUG_DETECTORS
	Serial.print(s_detector_average[0]);
	Serial.println(s_reel_detector_triggered[0] ? "(trig)" : "");
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
	if (motor == 0 || motor > NUMBER_OF_MOTORS)
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

static void set_motor_state(uint8_t motor, uint8_t new_state)
{
	s_move_state[motor] = (MOVE_STATE)new_state;
	
	if ((new_state == MS_STOPPED_MOTOR) || (new_state == MS_STOPPED_DETECTOR))
	{
		s_debug_task.SetInterval( 1000 );
	}
	else
	{
		s_debug_task.SetInterval( 100 );	
	}

	#ifdef DEBUG_MOTORS
	Serial.print("M");
	Serial.print(motor);
	Serial.print(" state ");
	Serial.print(new_state);
	
	switch(new_state)
	{
	case MS_STOPPED_MOTOR:
		Serial.print(": motor stop at ");
		Serial.print(s_motors[s_next_motor].currentPosition());
		break;
	case MS_STOPPED_DETECTOR:
		Serial.print(": detector stop at ");
		Serial.print(s_motors[s_next_motor].currentPosition());
		break;
	case MS_MOVING_AWAY_FROM_OLD_POSITION:
		Serial.print(": moving from ");
		Serial.print(s_motors[s_next_motor].currentPosition());
		break;
	}

	Serial.println("");
	#endif
}

static void process_next_command()
{
	if (s_next_direction_is_forwards)
	{
		s_motors[s_next_motor].move(STEPS_PER_WORD);
	}
	else
	{
		s_motors[s_next_motor].move(-STEPS_PER_WORD);
	}
	set_motor_state(s_next_motor, MS_MOVING_AWAY_FROM_OLD_POSITION);
}

static void setup_motors()
{
	uint8_t i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_motors[i].setMaxSpeed(200);
		s_motors[i].setAcceleration(100);	
	}
}

static void stop_motor(uint8_t motor)
{
	// Set the motor stop steps based on direction
	if (s_next_direction_is_forwards)
	{
		s_motors[motor].move(STEPS_TO_STOP_FORWARD);
	}
	else
	{
		s_motors[motor].move(-STEPS_TO_STOP_BACKWARD);
	}
}

static void run_motors()
{
	uint8_t i;
	bool motor_is_running = false;

	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		motor_is_running = s_motors[i].run();
		
		/* Decide if motor should keep turning or not */
		switch(s_move_state[i])
		{
			case MS_MOVING_AWAY_FROM_OLD_POSITION:
				// Wait for the detector to un-trigger from old position
				if (!s_reel_detector_triggered[i])
				{
					set_motor_state(i, MS_MOVING_TO_NEW_POSITION);
				}
				break;
			case MS_MOVING_TO_NEW_POSITION:
				if (motor_is_running)
				{
					// Wait for the detector to trigger at new position
					if (s_reel_detector_triggered[i])
					{
						stop_motor(i);
						set_motor_state(i, MS_STOPPED_DETECTOR);		
					}
				}				
				else
				{
					set_motor_state(i, MS_STOPPED_MOTOR);
				}
				break;
			default:
				break;
		}
	}
}

static void update_detectors()
{
	uint8_t i;
	
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_detector_average[i] += analogRead(s_detector_pins[i]);
		s_detector_average[i] /= 2;

		/* Use some hysteresis when detecting state change */
		if (s_reel_detector_triggered[i])
		{
			s_reel_detector_triggered[i] = (s_detector_average[i] >= 200);
		}
		else
		{
			s_reel_detector_triggered[i] = (s_detector_average[i] >= 300);	
		}
	}
}

static bool move_motor_until_trigger(uint8_t motor, float speed)
{
	bool start_trigger;

	update_detectors();

	start_trigger = s_reel_detector_triggered[motor];

	s_motors[motor].setSpeed(speed);
	do
	{
		update_detectors();
		s_debug_task.tick();
		s_motors[motor].runSpeed();
	} while (s_reel_detector_triggered[motor] == start_trigger);
}

static void initial_seek_to_word()
{

	/* Move at low speed and look for edges */
	int i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		// First move forward until an edge is reached - this provides a reference point
		move_motor_until_trigger(i, 200);
		#ifdef DEBUG_MOTORS
		Serial.println("Trigger point found.");
		#endif
		
		// Then move to centre the word
		if (s_reel_detector_triggered[i])
		{
			#ifdef DEBUG_MOTORS
			Serial.println("Moving forwards to word");
			#endif
			// Reel just triggered, move forwards to centre
			s_motors[i].move(50);
		}
		else
		{	
			#ifdef DEBUG_MOTORS
			Serial.println("Moving backwards to word");
			#endif
			// Reel just untriggered, move backwards to centre
			s_motors[i].move(-320);
		}

		while( s_motors[i].run() )
		{
			s_debug_task.tick();
		}
	}
}

static void fill_averages()
{
	int i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_detector_average[i] = analogRead(s_detector_pins[i]);
	}
}

/*
 * Arduino functions
 */

void setup()
{
	Serial.begin(115200);	
	setup_motors();

	fill_averages();

	#ifdef DEBUG_MOTORS
	Serial.println("Seeking motors.");
	#endif
	initial_seek_to_word();
	#ifdef DEBUG_MOTORS
	Serial.println("Seek complete.");
	#endif
}

void loop()
{
	if (s_command_ready)
	{
		process_next_command();
		s_command_ready = false;
	}

	update_detectors();
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
