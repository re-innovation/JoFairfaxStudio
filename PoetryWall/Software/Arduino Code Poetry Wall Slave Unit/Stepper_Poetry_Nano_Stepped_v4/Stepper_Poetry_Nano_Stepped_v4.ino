/* 
 * 3rd party libraries
 */

#include <AccelStepper.h>
#include <TaskAction.h>

/*
 * Defines and typedefs
 */

//#define DEBUG_MOTORS
//#define DEBUG_COMMANDS
//#define DEBUG_DETECTORS

#define NUMBER_OF_MOTORS (1)

#define DETECTOR_TRIGGER_THRESHOLD (500)

#define FORWARD_MOTION_EXTRA_STEPS (30)
#define BACKWARD_MOTION_EXTRA_STEPS (170)

#define FORWARD_SEEK_EXTRA_STEPS (50)
#define BACKWARD_SEEK_EXTRA_STEPS (230)

/* 
 * STEPS_PER_WORD is the ideal number of steps to move between words
 * From this and NUMBER_OF_WORDS, the steps per word and steps per divison
 * are derived.
 */
#define STEPS_PER_REV (6230L)
#define NUMBER_OF_WORDS (11L)

#define STEPS_PER_WORD (STEPS_PER_REV / (NUMBER_OF_WORDS-1))
#define STEPS_PER_DIVISION (STEPS_PER_WORD/2)

/* A motor can be in one of five states:
 * Stopped because the detector tripped (this should be the normal stopped state)
 * Stopped because the motor ran through its full number of steps-per-word
 *		- normally this shouldn't happen because the detector should trip and command a stop
 * Moving away from old stopped position towards first dectector edge
 * Moving to second detector edge
 * Stopping after second detector edge
 */
enum move_state
{
	MS_STOPPED_DETECTOR,
	MS_STOPPED_MOTOR,
	MS_MOVING_TO_FIRST_EDGE,
	MS_MOVING_TO_SECOND_EDGE,
	MS_STOPPING
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

static bool s_motor_is_running[NUMBER_OF_MOTORS] = {
	false,
	//false,
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

static uint32_t s_detector_values[NUMBER_OF_MOTORS];

static void debug_task_fn()
{
	#ifdef DEBUG_DETECTORS
	Serial.print(s_detector_values[0]);
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
	case MS_MOVING_TO_FIRST_EDGE:
		Serial.print(": moving to E1 from ");
		Serial.print(s_motors[s_next_motor].currentPosition());
		break;
	case MS_MOVING_TO_SECOND_EDGE:
		Serial.print(": moving to E2 from ");
		Serial.print(s_motors[s_next_motor].currentPosition());
		break;
	}

	Serial.println("");
	#endif

	if ((new_state == MS_STOPPED_MOTOR) || (new_state == MS_STOPPED_DETECTOR))
	{
		Serial.print("OK");
	}
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
	set_motor_state(s_next_motor, MS_MOVING_TO_FIRST_EDGE);
}

static void stop_motor(uint8_t motor)
{
	// Set the motor stop steps based on direction
	if (s_next_direction_is_forwards)
	{
		s_motors[motor].move(STEPS_PER_DIVISION + FORWARD_MOTION_EXTRA_STEPS);
	}
	else
	{
		s_motors[motor].move(-STEPS_PER_DIVISION - BACKWARD_MOTION_EXTRA_STEPS);
	}
}

static void handle_move_to_first_edge(int i)
{
	// Wait for the detector to un-trigger from old position
	if (!s_reel_detector_triggered[i])
	{
		set_motor_state(i, MS_MOVING_TO_SECOND_EDGE);
	}
	else if (!s_motor_is_running[i])
	{
		set_motor_state(i, MS_STOPPED_MOTOR);
	}
}

static void handle_move_to_second_edge(int i)
{
	if (s_motor_is_running[i])
	{
		// Wait for the detector to trigger at new position
		if (s_reel_detector_triggered[i])
		{
			stop_motor(i);
			set_motor_state(i, MS_STOPPING);		
		}
	}				
	else
	{
		set_motor_state(i, MS_STOPPED_MOTOR);
	}
}

static void handle_stopping(int i)
{
	if (!s_motor_is_running[i])
	{
		set_motor_state(i, MS_STOPPED_DETECTOR);
	}
}

static void run_motors()
{
	uint8_t i;
	
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_motor_is_running[i] = s_motors[i].run();
		
		/* Handle motor motion based on its current state */
		switch(s_move_state[i])
		{
			case MS_MOVING_TO_FIRST_EDGE:
				handle_move_to_first_edge(i);
				break;
			case MS_MOVING_TO_SECOND_EDGE:
				handle_move_to_second_edge(i);
				break;
			case MS_STOPPING:
				handle_stopping(i);
				break;
			default:
				break;
		}
	}
}

static void update_detector(int detector_index)
{
	s_detector_values[detector_index] = analogRead(s_detector_pins[detector_index]);
	s_reel_detector_triggered[detector_index] = s_detector_values[detector_index] < DETECTOR_TRIGGER_THRESHOLD;
}

static void update_detectors()
{
	uint8_t i;
	
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		update_detector(i);		
	}
}

static bool move_motor_until_trigger_changed(uint8_t motor, float speed)
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

	return !start_trigger;
}

static void initial_seek_to_word()
{

	/* Move at low speed and look for edges */
	int i;
	int first_edge_was_low;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{

		// First move forward until an edge is reached - this provides a reference point
		first_edge_was_low = move_motor_until_trigger_changed(i, 100);
		
		s_motors[i].setCurrentPosition(0);

		#ifdef DEBUG_MOTORS
		Serial.print("Trigger point found (");
		Serial.print(first_edge_was_low ? "low" : "high");
		Serial.println("). Moving to word.");
		#endif
		
		// Then move to centre the word
		if (first_edge_was_low)
		{
			// Reel just triggered, move forwards to centre
			s_motors[i].moveTo(STEPS_PER_DIVISION + FORWARD_SEEK_EXTRA_STEPS);

		}
		else
		{	
			// Reel just untriggered, move fowards to centre
			s_motors[i].moveTo(STEPS_PER_DIVISION - BACKWARD_SEEK_EXTRA_STEPS);
		}

		s_motors[i].setSpeed(100);

		while( s_motors[i].distanceToGo() )
		{
			s_motors[i].runSpeed();
			s_debug_task.tick();
		}
	}
}

static void fill_averages()
{
	int i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_detector_values[i] = analogRead(s_detector_pins[i]);
	}
}

static void setup_motors_for_init()
{
	uint8_t i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		// Setting a very high accelleration means that start/stop is effectively instanteneous,
		// which is nicer for finding initial position
		s_motors[i].setAcceleration(1000);
		s_motors[i].setMaxSpeed(200);
	}
}

static void setup_motors_for_run()
{
	uint8_t i;
	for (i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		s_motors[i].setAcceleration(100);	
	}
}

/*
 * Arduino functions
 */

void setup()
{
	Serial.begin(115200);	
	setup_motors_for_init();

	fill_averages();

	#ifdef DEBUG_MOTORS
	Serial.println("Seeking motors.");
	#endif
	initial_seek_to_word();
	#ifdef DEBUG_MOTORS
	Serial.println("Seek complete.");
	#endif

	setup_motors_for_run();
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
