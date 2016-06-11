/*
 * The configuration for each unit is contained in the .ino file,
 * where the WordReel objects are declared.
 *
 * This file contains the declarations for each unit (master and 4 slaves).
 * When the configuration for unit changes, copy-and-paste it into this
 * file to keep a record of the setup for all units.
 *
 * Do not #include this file in any code files!
 */

/*
 * Master
 */

static WordReel s_reels[NUMBER_OF_MASTER_REELS] = {
  WordReel(
    5, 7, 6, 8,               // Motor pins
    A4,                       // Detector pin
    0,                        // Motor ID
    560,                      // Forward steps to centre word at setup
    200, 30,                  // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_master_move_complete_motor1), // Function to call when move is complete
  WordReel(
    9, 11, 10, 12,            // Motor pins
    A5,                       // Detector pin
    1,                        // Motor ID
    289,                      // Forward steps to centre word at setup
    -20, 0,                // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_master_move_complete_motor2), // Function to call when move is complete
};

/*
 * Slave 00
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

/*
 * Slave 01
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

/*
 * Slave 02
 */

static WordReel s_reels[NUMBER_OF_REELS] = {
	WordReel(
		5, 7, 6, 8,			// Motor pins
		A5,					// Detector pin
		1,					// Motor ID
		210,
		0, -200, 			// Forward and backward steps to centre word when running
		true, 				// Invert fwd/back movement sense
		on_move_complete_1),	// Function to call when move is complete

	WordReel(
		9, 11, 12, 10,
		A4,
		2,
		30,
		0, -30,
		false,
		on_move_complete_2)
};

/*
 * Slave 03
 */

static WordReel s_reels[NUMBER_OF_REELS] = {
	WordReel(
		5, 7, 6, 8,			// Motor pins
		A4,					// Detector pin
		1,					// Motor ID
		130,
		0, -100, 			// Forward and backward steps to centre word when running
		true, 				// Invert fwd/back movement sense
		on_move_complete_1),	// Function to call when move is complete

	WordReel(
		9, 11, 12, 10,
		A5,
		2,
		410,
		0, 170,
		false,
		on_move_complete_2)
};
