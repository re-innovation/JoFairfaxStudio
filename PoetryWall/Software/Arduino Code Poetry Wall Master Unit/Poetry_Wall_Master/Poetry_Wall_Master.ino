/*
  Poetry Wall Code: MASTER UNIT

  This runs a stepper motor (or motors) from an Arduino Nano
  5V ATMEGA328 16MHz (12MHz?)

  I'm using the 28BYJ-48 stepper motor with driver
  This Motor has a Gear ratio of 64 , and Stride Angle 5.625°
  so this motor has a 4096 Steps .

  Lots more info here:
  http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/

  Gear ratio is: 64 approx :1
  Actual gear ratio: 63.68395 : 1

  The PCB has the following wiring:

  Stepper Motor Set 1 (6 x motors) is on:
  D5,D6,D7,D8

  Stepper Motor Set 2 (6 x motors) is on:
  D9,D10,D11,D12

  Connectors K1/K2/K3/K4 decide if all 12 Motors do the same thing or
  if there are two sets of 6 motors which can do different things.

  INPUTS:
  RESET  D2
  SW1    D3
  SW2    D4

  DETECT_IN1
  A0
  A1  EchoPin
  A2  TrigPin

  A3  N/C

  A4  Photo Detector M1
  A5  Photo Detector M2
  A6  

  This code has the following functions:

  The code as a whole will
  MASTER UNIT:
  The MASTER unit will monitor the ultrasonic sensor.
  If detected then it will randomly choose 1,2,3 or 4 words to change.
  This will be from a random seed.
  The motors are called via serial line (at 9600 baud) using the format:
  aXXMYYD----
  Where XX is an ID for the slave unit, YY is the motor ID and D is the direction (F/B)


  This example code is in the public domain.
 */
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>

#include <AccelStepper.h>
#include <SoftwareSerial.h>

#include "debug_config.h"
#include "word_reel.h"

#define TRIG_PIN A2  //  The connections for the ultrasonic distance sensor
#define ECHO_PIN A1

#define NUMBER_OF_MASTER_REELS (2)
#define NUMBER_OF_SLAVE_REELS (10)

#define NUMBER_OF_REELS_TOTAL (NUMBER_OF_MASTER_REELS + NUMBER_OF_SLAVE_REELS)

#define WHEELS_TO_MOVE_PER_TRIGGER (3)

#define MINIMUM_TRIGGER_DISTANCE 5
#define MAXIMUM_TRIGGER_DISTANCE 15

#define RESET_PIN (2)
#define CMD_RX_PIN (3)
#define CMD_TX_PIN (4)

#define SERIAL_TIMEOUT_MS (6000UL)

#define LED_PIN (13)

static int motor1 = 0; // Holds the ID for Motor 1
static int motor2 = 0; // Holds the ID for Motor 2

// Declare one reel on the master unit
static WordReel s_reels[NUMBER_OF_MASTER_REELS] = {
  WordReel(
    5, 7, 6, 8,               // Motor pins
    A4,                       // Detector pin
    0,                        // Motor ID
    50, 250,                  // Forward and backward steps to centre word at setup
    30, 170,                  // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_master_move_complete), // Function to call when move is complete
  WordReel(
    9, 11, 10, 12,            // Motor pins
    A5,                       // Detector pin
    1,                        // Motor ID
    50, 250,                  // Forward and backward steps to centre word at setup
    30, 170,                  // Forward and backward steps to centre word when running
    true,                     // Invert fwd/back movement sense
    on_master_move_complete), // Function to call when move is complete
};

static SoftwareSerial s_serial_cmd(CMD_RX_PIN, CMD_TX_PIN);

static bool s_wait = false;

// ****************USER VARIABLES****************************************
// **********************************************************************

// Each reel is associated with a two-digit unit ID.
// This array maps between reels and unit ID
static char reel_to_unit_id_map[NUMBER_OF_SLAVE_REELS][3] = {
  "00", // Reel 1 is on slave 00
  "00",  // Reel 2 is on slave 00
  "01", // Reel 1 is on slave 00
  "01",  // Reel 2 is on slave 00
  "02", // Reel 1 is on slave 00
  "02",  // Reel 2 is on slave 00
  "03", // Reel 1 is on slave 00
  "03",  // Reel 2 is on slave 00
  "04", // Reel 1 is on slave 00
  "04", // Reel 1 is on slave 00
};

// Each reel is associated with two-digit motor ID.
// This array maps between reels and motor ID
static char reel_to_motor_id_map[NUMBER_OF_SLAVE_REELS][3] = {
  "01", // Slave 1, reel 1
  "02",  // Slave 1, reel 2
  "01", // Slave 1, reel 1
  "02",  // Slave 1, reel 2
  "01", // Slave 1, reel 1
  "02",  // Slave 1, reel 2
  "01", // Slave 1, reel 1
  "02",  // Slave 1, reel 2
  "01", // Slave 1, reel 1
  "02"  // Slave 1, reel 2
};

// ********************* END OF USER VARIABLES***************************
// **********************************************************************

static int get_ultrasonic_distance()
{
  int distance = 0;
  unsigned long duration;

  // This section of code reads the ultrasonic distance sensor delay
  for(int i = 0; i<=10; i++)
  {
    digitalWrite(TRIG_PIN, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(1000); // Added this line
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH, 500000);
    distance += (duration/2) / 29.1;
    delay(2);
  }
  distance = distance/10;  // Averaging

  #ifdef DEBUG_ULTRASONIC
    Serial.print("Ultrasonic:");
    Serial.print(distance);
    Serial.println(" cm");  
  #endif

  return distance;
}

static char reel_direction_is_forwards(int reel)
{
  return (reel % 2) == 0;
}

static char * make_new_command(int reel)
{
  static char commandBuffer[13];

  commandBuffer[0] = 'a'; // Commands always start with 'a';

  // Convert from master reel number to slave reel number
  reel -= NUMBER_OF_MASTER_REELS;

  // Map reel number to unit ID
  commandBuffer[1] = reel_to_unit_id_map[reel][0];
  commandBuffer[2] = reel_to_unit_id_map[reel][1];

  commandBuffer[3] = 'M';

  commandBuffer[4] = reel_to_motor_id_map[reel][0];
  commandBuffer[5] = reel_to_motor_id_map[reel][1];

  commandBuffer[6] = reel_direction_is_forwards(reel) ? 'F' : 'B';

  strncpy(&commandBuffer[7], "-----", 5);
  commandBuffer[12] = '\0';
  
  commandBuffer[12] = '\0';

  return commandBuffer;
}

static void run_motors()
{
  uint8_t i;
  
  for (i = 0; i < NUMBER_OF_MASTER_REELS; i++)
  {
    s_reels[i].update_detector();
    s_reels[i].run();
  }
}

static void read_software_serial_blocking(int expected, int timeout=0)
{

  // Block until data available.
  if (timeout == 0)
  {
      while(s_serial_cmd.available()<expected);
  }
  else
  {
      unsigned long start = millis();
      bool got_expected = false;
      while ((millis() - start) < timeout)
      {
        got_expected = (s_serial_cmd.available() >= expected);
        if (got_expected) { break; }  
      }

      if (!got_expected)
      {
        Serial.println("Serial timeout!");
      }
  }

  #ifdef ECHO_SERIAL_INPUT

  String serialInput;
  
  if(s_serial_cmd.available()>= expected)
  {
    for (int i=0;i<expected;i++)
    {
      serialInput += (char)s_serial_cmd.read();    
    } 
    Serial.println(serialInput);
  }
  #endif
}

static bool reel_is_on_master(int reel)
{
  return (reel < NUMBER_OF_MASTER_REELS);
}

static void move_master_reel(int reel)
{
  s_wait = true;

  bool forwards = reel_direction_is_forwards(reel);
  s_reels[reel].move_one_word(forwards);

  while(s_wait) {
    run_motors();
  }

  s_reels[reel].off();
}

static void on_master_move_complete()
{
  s_wait = false;
}

static void move_slave_reel(int reel)
{
  char * cmd = make_new_command(reel);

  #ifdef DEBUG_REEL_SELECTION
  Serial.print("Sending ");
  Serial.println(cmd);
  #endif

  s_serial_cmd.println(cmd); 
  s_serial_cmd.flush();

  // Expect two characters back from slave
  read_software_serial_blocking(2, SERIAL_TIMEOUT_MS);
}

static void create_random_number_array(int * pRandArray)
{
    for (int i=0;i<NUMBER_OF_REELS_TOTAL;i++)
    {    
      // Here we want to check if its the same as any previous numbers
      bool same;
      do
      {
        same = false;
        pRandArray[i] = random(0, NUMBER_OF_REELS_TOTAL);
        for(int y=0;y<i;y++)
        {
          same = same || (pRandArray[y] == pRandArray[i]);
        }
      } while(same);

      #ifdef DEBUG_REEL_SELECTION
      Serial.print(pRandArray[i]);
      Serial.print(" ");
      #endif
    }
    
    #ifdef DEBUG_REEL_SELECTION
    Serial.println("");
    #endif
}

static bool switch_is_pressed()
{
  return digitalRead(RESET_PIN)==LOW;
}

static bool distance_within_limits(int distance)
{
  return ((distance <= MAXIMUM_TRIGGER_DISTANCE) && (distance >= MINIMUM_TRIGGER_DISTANCE));
}

#ifdef DEBUG_TRIGGER_STATE
static void debug_trigger_state(char trigger_state)
{
    Serial.print("Triggered from  ");
    switch (trigger_state)
    {
    case 1:
      Serial.println("switch.");
      break;
    case 2:
      Serial.println("distance.");
      break;
    case 3:
      Serial.println("both.");
      break;
    }
}
#endif

static void trigger_reels_from_array(int * pRandArray)
{
  for(int z=0; z<WHEELS_TO_MOVE_PER_TRIGGER; z++)
  {
    int reelNumber = pRandArray[z];

    for (int j = 0; j < reelNumber; j++)
    {
        digitalWrite(LED_PIN, LOW);
        delay(100);
        digitalWrite(LED_PIN, HIGH);
        delay(100);
    }
    digitalWrite(LED_PIN, LOW);
        
    #ifdef DEBUG_REEL_SELECTION
    Serial.print("Moving reel ");
    Serial.print(reelNumber);
    Serial.print(reel_direction_is_forwards(reelNumber) ? " fwd" : " bck");
    #endif
    
    if (reel_is_on_master(pRandArray[z]))
    {
      #ifdef DEBUG_REEL_SELECTION
      Serial.println(" (master).");
      #endif
      move_master_reel(reelNumber);
    }
    else
    {
      #ifdef DEBUG_REEL_SELECTION
      Serial.println(" (slave).");
      #endif
      move_slave_reel(reelNumber);
    }
  }
}

static char get_trigger_state()
{
  int distance = get_ultrasonic_distance();
  char trigger_state = 0;

  trigger_state += switch_is_pressed() ? 1 : 0;
  trigger_state += distance_within_limits(distance) ? 2 : 0;

  return trigger_state;
}

static void process_trigger_state(char trigger_state)
{
  int randArray[NUMBER_OF_REELS_TOTAL];  // Creates an int array for holding the random numbers

  if(trigger_state)
  {
    #ifdef DEBUG_TRIGGER_STATE
    debug_trigger_state(trigger_state);
    #endif

    create_random_number_array(randArray);

    trigger_reels_from_array(randArray);
  }
}

void setup() {

  // Initialise the DIO a input with a pull up resistor
  pinMode(RESET_PIN, INPUT_PULLUP);
  
  pinMode(LED_PIN, OUTPUT); // Have the LED display an output

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
  s_serial_cmd.begin(9600);

  // Move all reels to initial positions
  int i;
  for (i = 0; i < NUMBER_OF_MASTER_REELS; i++)
  {
    s_reels[i].initial_seek_to_word();
    s_reels[i].off();
  }

  // Retrieve the setpoints from EEPROM
  motor1 = EEPROM.read(2);
  #ifdef DEBUG_EEPROM
  Serial.print("Motor1 ID:");
  Serial.println(motor1);
  motor2 = EEPROM.read(3);  
  Serial.print("Motor2 ID:");
  Serial.println(motor2);  
  #endif

  switch_off_motors();

}//--(end setup )---

void loop() {

  int trigger_state = get_trigger_state();
  
  process_trigger_state(trigger_state);

  run_motors();

}

void switch_off_motors()
{
  int i;
  for (i = 0; i < NUMBER_OF_MASTER_REELS; i++)
  {
    s_reels[i].off();
  }
}
