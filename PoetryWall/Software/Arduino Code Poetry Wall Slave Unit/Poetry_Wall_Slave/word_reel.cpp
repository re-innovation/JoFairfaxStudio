#include <Arduino.h>
#include <AccelStepper.h>

#include "debug_config.h"

#include "word_reel.h"

WordReel::WordReel(int m1_pin, int m2_pin, int m3_pin, int m4_pin, int detector_pin, int id,
	int extra_seek_steps_falling_edge, int extra_seek_steps_rising_edge,
	int extra_move_steps_fwd, int extra_move_steps_bck,
	bool invert_direction,
	ON_MOVE_COMPLETE_CALLBACK cb)
{
	m_motor = new AccelStepper(8, m1_pin, m2_pin, m3_pin, m4_pin);
	m_detector_pin = detector_pin;
	m_running = false;
	m_detector_triggered = false;
	m_state = MS_STOPPED_MOTOR;
	m_id = id;
	m_invert_direction = invert_direction;

	m_seek_steps_from_falling_edge = extra_seek_steps_falling_edge;
	m_seek_steps_from_rising_edge = extra_seek_steps_rising_edge;

	m_move_steps_fwd = extra_move_steps_fwd;
	m_move_steps_bck = extra_move_steps_bck;

	m_pins[0] = m1_pin;
	m_pins[1] = m2_pin;
	m_pins[2] = m3_pin;
	m_pins[3] = m4_pin;

	m_callback = cb;
	pinMode(detector_pin, INPUT);
}

void WordReel::setup_for_init()
{
	// Setting a very high accelleration means that start/stop is effectively instanteneous,
	// which is nicer for finding initial position
	m_motor->setAcceleration(1000);
	m_motor->setMaxSpeed(200);
}

void WordReel::setup_for_run()
{
	m_motor->setAcceleration(100);
}

void WordReel::set_motor_state(uint8_t new_state)
{
	m_state = (MOVE_STATE)new_state;
	
	if ((new_state == MS_STOPPED_MOTOR) || (new_state == MS_STOPPED_DETECTOR))
	{
		if (m_callback){ m_callback(); }
	}
}

void WordReel::handle_move_to_first_edge()
{
	// Wait for the detector to un-trigger from old position
	if (!m_detector_triggered)
	{
		set_motor_state(MS_MOVING_TO_SECOND_EDGE);
	}
	else if (!m_running)
	{
		set_motor_state(MS_STOPPED_MOTOR);
	}
}

void WordReel::handle_move_to_second_edge()
{
	if (m_running)
	{
		// Wait for the detector to trigger at new position
		if (m_detector_triggered)
		{
			set_stop_target();
			set_motor_state(MS_STOPPING);		
		}
	}				
	else
	{
		set_motor_state(MS_STOPPED_MOTOR);
	}
}

void WordReel::handle_stopping()
{
	if (!m_running)
	{
		set_motor_state(MS_STOPPED_DETECTOR);
	}
}

void WordReel::move_one_word(bool direction_is_forwards)
{
	m_direction_forwards = direction_is_forwards;

	if (m_invert_direction) { m_direction_forwards = !m_direction_forwards; }

	if (m_direction_forwards)
	{
		m_motor->move(STEPS_PER_WORD);
	}
	else
	{
		m_motor->move(-STEPS_PER_WORD);
	}
	set_motor_state(MS_MOVING_TO_FIRST_EDGE);
}

void WordReel::set_stop_target()
{
	// Set the motor stop steps based on direction
	if (m_direction_forwards)
	{
		#ifdef DEBUG_MOTORS
		print_name();
		Serial.print(": Fwd. stop target:");
		Serial.println(STEPS_PER_DIVISION + m_move_steps_fwd);
		#endif
		m_motor->move(STEPS_PER_DIVISION + m_move_steps_fwd);
	}
	else
	{
		#ifdef DEBUG_MOTORS
		print_name();
		Serial.print(": Bck. stop target:");
		Serial.println(-STEPS_PER_DIVISION - m_move_steps_bck);
		#endif
		m_motor->move(-STEPS_PER_DIVISION - m_move_steps_bck);
	}
}

void WordReel::run()
{
	m_running = m_motor->run();
	
	/* Handle motor motion based on its current state */
	switch(m_state)
	{
		case MS_MOVING_TO_FIRST_EDGE:
			handle_move_to_first_edge();
			break;
		case MS_MOVING_TO_SECOND_EDGE:
			handle_move_to_second_edge();
			break;
		case MS_STOPPING:
			handle_stopping();
			break;
		default:
			break;
	}

}

bool WordReel::move_until_trigger_changed(float speed)
{
	bool start_trigger;

	update_detector();

	start_trigger = m_detector_triggered;

	m_motor->setSpeed(speed);
	
	do
	{
		update_detector();
		if (m_motor->runSpeed())
		{
			#ifdef DEBUG_DETECTORS
			print_name();
			Serial.print(" :");
			Serial.print(detectorValue());
			Serial.println(isTriggered() ? " (trig)" : "");
			#endif
		}
	} while (m_detector_triggered == start_trigger);

	return !start_trigger;
}

/*
 * print_name
 *
 * Print this motor's ID to the serial port
 */

void WordReel::print_name()
{
	Serial.print("Motor ");
	Serial.print(m_id);
}

/*
 * initial_seek_to_word
 *
 * Move forward and low speed and looks for an edge
 * then moves from that edge to centre the next word
 */
void WordReel::initial_seek_to_word()
{
	#ifdef DEBUG_MOTORS
	print_name();
	Serial.println(": Starting initial seek.");
	#endif

	setup_for_init();

	// First move forward until an edge is reached - this provides a reference point
	bool first_edge_was_falling = move_until_trigger_changed(100);
	
	#ifdef DEBUG_MOTORS
	print_name();
	Serial.print(": Found first edge. Moving to centre (");
	Serial.print(first_edge_was_falling ? "FWD" : "BCK");
	Serial.println(").");
	#endif

	m_motor->setCurrentPosition(0);

	// Then move to centre the word
	if (first_edge_was_falling)
	{
		// Reel just triggered, move forwards to centre
		m_motor->moveTo(m_seek_steps_from_falling_edge);

	}
	else
	{	
		// Reel just untriggered, move fowards to centre
		m_motor->moveTo(m_seek_steps_from_rising_edge);
	}

	m_motor->setSpeed(100);

	while( m_motor->distanceToGo() )
	{
		m_motor->runSpeed();
	}

	setup_for_run();

	#ifdef DEBUG_MOTORS
	print_name();
	Serial.println(": Ready!");
	#endif
}

void WordReel::wait_for_newline()
{
	while (Serial.read() != '\n') {}	
}

void WordReel::flush_incoming_serial()
{
	while(Serial.available()) { (void)Serial.read(); }
}

void WordReel::interactive_calibrate_edge(bool falling)
{
	bool stop = false;

	// Move till specified edge
	while( falling != move_until_trigger_changed(100) ) {}
	
	flush_incoming_serial();

	print_name();
	Serial.print(": Found ");
	Serial.print(falling ? "falling" : "rising");
	Serial.println(" edge. Ready to move to word.");
	print_name();
	Serial.println(": Send a newline ('\\n') to start");
	print_name();
	Serial.println(": Send a second newline when the word has centred.");

	wait_for_newline();

	m_motor->setCurrentPosition(0);
	m_motor->setSpeed(100);

	while( !stop )
	{
		m_motor->runSpeed();
		stop = Serial.available() && Serial.read() == '\n';
	}

	print_name();
	Serial.print(": Stopped at ");
	Serial.println(m_motor->currentPosition());
	Serial.println();

	flush_incoming_serial();

	if (falling)
	{
		m_seek_steps_from_falling_edge = m_motor->currentPosition();
	}
	else
	{
		m_seek_steps_from_rising_edge = m_motor->currentPosition();	
	}
}

void WordReel::interactive_calibrate_move(bool forwards)
{

	int * p_move_steps = forwards ? &m_move_steps_fwd : &m_move_steps_bck;
	print_name();
	Serial.print(": Moving one word ");
	Serial.println(forwards ? "forwards." :" backwards.");

	*p_move_steps = 0;

	while(true)
	{
		print_name();
		Serial.print(": Current steps = ");
		Serial.print(forwards ? m_move_steps_fwd : m_move_steps_bck);
		Serial.println(".");

		move_one_word(forwards ^ m_invert_direction);

		do
		{
			update_detector();
			run();
		} while(m_running);

		print_name();
		Serial.print(": Stopped due to ");
		Serial.println(m_state == MS_STOPPED_MOTOR ? "motor." : "detector.");
		
		print_name();
		Serial.println(": Enter new value or -1 to finish.");

		int new_steps = Serial.parseInt();
		
		if (new_steps == -1) { break; }

		*p_move_steps = new_steps;
	}

	print_name();
	Serial.print(": Finished ");
	Serial.print(forwards ? "forward " :" backward");
	Serial.print(" move calibration at ");
	Serial.print(forwards ? m_move_steps_fwd : m_move_steps_bck);
	Serial.println(" steps.");

	flush_incoming_serial();
}

void WordReel::run_interactive_calibration()
{
	setup_for_init();

	Serial.println();

	print_name();
	Serial.println(": Interactive calibration");
	print_name();
	Serial.println(": Send a newline ('\\n') to start falling edge calibration");

	flush_incoming_serial();
	wait_for_newline();
	interactive_calibrate_edge(true);

	print_name();
	Serial.println(": Send a newline ('\\n') to start rising edge calibration");

	wait_for_newline();
	interactive_calibrate_edge(false);

	initial_seek_to_word();

	print_name();
	Serial.println(": Send a newline ('\\n') to start forward move calibration");
	
	wait_for_newline();
	interactive_calibrate_move(true);

	print_name();
	Serial.println(": Send a newline ('\\n') to start backward move calibration");
	
	wait_for_newline();
	interactive_calibrate_move(false);

	print_name();
	Serial.print(": calibration complete. Final values:");
	Serial.print(m_seek_steps_from_falling_edge);
	Serial.print(", ");
	Serial.print(m_seek_steps_from_rising_edge);
	Serial.print(", ");
	Serial.print(m_move_steps_fwd);
	Serial.print(", ");
	Serial.print(m_move_steps_bck);	
}

void WordReel::update_detector()
{
	m_last_detector_value = analogRead(m_detector_pin);
	m_detector_triggered = m_last_detector_value < DETECTOR_TRIGGER_THRESHOLD;
}

void WordReel::off()
{
	digitalWrite(m_pins[0], LOW);
	digitalWrite(m_pins[1], LOW);
	digitalWrite(m_pins[2], LOW);
	digitalWrite(m_pins[3], LOW);
}
