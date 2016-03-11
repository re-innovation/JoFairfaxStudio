#ifndef _WORD_REEL_H_
#define _WORD_REEL_H_

#define DETECTOR_TRIGGER_THRESHOLD (500)

/* 
 * STEPS_PER_WORD is the ideal number of steps to move between words
 * From this and NUMBER_OF_WORDS, the steps per word and steps per divison
 * are derived.
 */
#define STEPS_PER_REV (6230L)
#define NUMBER_OF_WORDS (10L)

#define STEPS_PER_WORD (STEPS_PER_REV / (NUMBER_OF_WORDS-1))
#define STEPS_PER_DIVISION (STEPS_PER_WORD/2)

typedef void (*ON_MOVE_COMPLETE_CALLBACK)(void);

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

class WordReel
{
public:
	WordReel(int m1_pin, int m2_pin, int m3_pin, int m4_pin, int detector_pin, int id,
		int extra_seek_steps_fwd, int extra_seek_steps_bck,
		int extra_move_steps_fwd, int extra_move_steps_bck,
		bool invert_direction,
		ON_MOVE_COMPLETE_CALLBACK cb);

	int detectorValue() { return m_last_detector_value; }
	bool isTriggered() { return m_detector_triggered; }

	void initial_seek_to_word();
	
	void run_interactive_calibration();

	void move_one_word(bool direction_is_forwards);
	void run();

	void update_detector();
	
	void off();
	
private:
	int m_id;
	AccelStepper * m_motor;
	int m_detector_pin;
	bool m_running;
	MOVE_STATE m_state;
	bool m_detector_triggered;
	int m_last_detector_value;
	bool m_direction_forwards;
	bool m_invert_direction;
	
	int m_seek_steps_from_falling_edge;
	int m_seek_steps_from_rising_edge;

	int m_move_steps_fwd;
	int m_move_steps_bck;

	char m_pins[4];
	
	ON_MOVE_COMPLETE_CALLBACK m_callback;

	void set_motor_state(uint8_t new_state);

	void setup_for_init();
	void setup_for_run();

	void handle_move_to_first_edge();
	void handle_move_to_second_edge();
	void handle_stopping();
	void set_stop_target();

	bool move_until_trigger_changed(float speed);

	void print_name();

	void wait_for_newline();
	void flush_incoming_serial();

	void interactive_calibrate_edge(bool falling);
	void interactive_calibrate_move(bool forwards);
};


#endif
