#include <Arduino.h>
#include <AccelStepper.h>

#include "debug_config.h"

#include "word_reel.h"

WordReel::WordReel(int m1_pin, int m2_pin, int m3_pin, int m4_pin, int detector_pin, int id,
	int extra_seek_steps_fwd, int extra_seek_steps_bck,
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

	m_seek_steps_fwd = extra_seek_steps_fwd;
	m_seek_steps_bck = extra_seek_steps_bck;

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
		m_motor->move(STEPS_PER_DIVISION + m_move_steps_fwd);
	}
	else
	{
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

	int i;

	setup_for_init();

	// First move forward until an edge is reached - this provides a reference point
	int first_edge_was_low = move_until_trigger_changed(100);
	
	#ifdef DEBUG_MOTORS
	print_name();
	Serial.print(": Found first edge. Moving to centre (");
	Serial.print(first_edge_was_low ? "FWD" : "BCK");
	Serial.println(").");
	#endif

	m_motor->setCurrentPosition(0);

	// Then move to centre the word
	if (first_edge_was_low)
	{
		// Reel just triggered, move forwards to centre
		m_motor->moveTo(STEPS_PER_DIVISION + m_seek_steps_fwd);

	}
	else
	{	
		// Reel just untriggered, move fowards to centre
		m_motor->moveTo(STEPS_PER_DIVISION - m_seek_steps_bck);
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
