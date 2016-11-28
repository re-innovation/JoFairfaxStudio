/*
  The code for a Solar Powered Birdsong Unit
  This is recharged by solar PV power
  It has a PIR which sets off birdsong stored onto
  a SoundOut MP3 Audio Module (EA MOD 1021) from Embedded Adventures
  http://www.embeddedadventures.com/soundout_mp3_module_mod-1021.html

  The power to the sound unit and amplifier are controlled
  using a digital output pin.

  This must have a decent power supply (eg. battery) or it will brown-out reset.

  This runs on 
  A Nano 5V
  A SoundOut MP3 Audio Module (EA MOD 1021) from Embedded Adventures
  http://www.embeddedadventures.com/soundout_mp3_module_mod-1021.html
  A li-po rider + PV module is used to recharge a 2000mAh li-ion battery
  A simple PIR sensor is used to trigger the unit.

  To reduce power consumption the unit goes to sleep a LOT.
  An interuupt from the PIR pin causes it to wake up
  
  If its triggered the a random sound file is played.
  If not then it just goes back to sleep again.
  Current when asleep = 1-1.5mA
  Current when awake = 20mA
  Current when playing sounds = 100-200mA.

  More infomation here:
  matt@re-innovation.co.uk
  www.re-innovation.co.uk

*/

/*
  Updates:
  5/5/15  First version of the code - Matt Little
  1/6/15  Adding sleep code to reduce power consumption - Matt Little
*/

#include <stdlib.h>
//#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <SoftwareSerial.h>

// ***** Digital I/O *********
#define powerControl  5
#define pirInterrupt 2
#define led 13

// Sound Module Connections
//#define RST 9    // change - pin 11
#define TX 11    // " 12
#define RX 10   // " 13

// Define the MP3 Module's Commands that we'll be using
#define cmdNextTrack  0x01                  // Next track.      
#define cmdPrevTrack  0x02                  // Previous track.
#define cmdRepeatPlay 0x11                  // Repeat play.

#define cmdSetVolume  0x06                  // Set Volume to a specified value.
#define cmdSetEq      0x07                  // Set Equalizer to a specified value.
#define cmdReset      0x0c                  // Reset MP3 Module.
#define cmdsdTracks   0x47                  // Reset MP3 Module.

// ******* Analogue I/O **********
int tuneBusy = A0;  // Measure when the audio module has finnished.

int tune;  // This is the tune file to play
int tuneMax = 20;  // This is the maximum tune ID (usually 20)

int sensorValue = 0;  // Holds the busy pin sensor value.

boolean busyPin = 0;  // This is a flag for the busyPin

SoftwareSerial mp3(RX, TX); // RX, TX

unsigned int volume = 10;                   // Starting MP3 module volume (0 - 31).
unsigned int eq = 0;                        // Normal/Pop/Rock/Jazz/Classic/Base equalizer.

unsigned int playTune = 0;  // This holds a random number from

byte data[10];
char inByte;

// Initialize send buffer for MP3 module command string.
byte cmdBuff[10] = {0x7e,                   // Start Byte, always 0x7e.
                    0xff,                   // Version, always 0xff.
                    0x06,                   // Data length, always 0x06 for us.
                    0x00,                   // Command value.
                    0x00,                   // Feedback, always 0x00 ('No feedback') for us.
                    0x00,                   // Command parameter Hi Byte.
                    0x00,                   // Command paramemer Lo Byte.
                    0x00,                   // Checksum Hi Byte.
                    0x00,                   // Checksum Lo Byte.
                    0xef                    // End Byte, always 0xef.
                   };


void interruptPIR() {
  // Want to wake up from sleep here
}



/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{
  
  // Attach interrupt again
  attachInterrupt(digitalPinToInterrupt(pirInterrupt), interruptPIR, RISING);
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();
  
  /* The program will continue from here. */
  
  /* First thing to do is disable sleep. */
  sleep_disable(); 
}

void setup()
{
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(powerControl, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tuneBusy, INPUT);

  Serial.begin(9600);

  digitalWrite(led, HIGH);
  digitalWrite(powerControl, HIGH);

  mp3.begin(9600);                              // Initialise software serial.
  delay(150);
  sendCommand(cmdReset, 1);                     // Reset MP3 module (command, parameter).
  delay(500);

  // set volume and equaliser? //
  
  //mp3.end();
  digitalWrite(led, LOW);             // MP3 module busy signal is active low.
  digitalWrite(powerControl, LOW);
  
  randomSeed(analogRead(A3));  // Read a disconnected pin to seed the random algorithm
  
  // Attach Interrupt
  pinMode(pirInterrupt, INPUT);
  attachInterrupt(digitalPinToInterrupt(pirInterrupt), interruptPIR, RISING);
}



// Routine to build 10-byte command buffer and write to software serial Tx (MP3 module Rx).
void sendCommand(byte Cmd, unsigned int Param) {
  unsigned int sum = 0;
  cmdBuff[3] = Cmd;                    // Command.
  cmdBuff[5] = (byte) (Param >> 8);    // Param Hi byte.
  cmdBuff[6] = (byte) (Param);         // Param Lo byte.

  for (int i = 1; i < 7; i++) {        // Calculate 16-bit checksum from buffer bytes 1 to 6.
    sum -= cmdBuff[i];
  }

  cmdBuff[7] = (byte) (sum >> 8);      // Add checksum Hi byte to buffer.
  cmdBuff[8] = (byte) sum;             // Add checksum Lo byte to buffer.

  for (int i = 0; i < 10; i++)
  { // Write entire buffer to software serial (mp3).
    mp3.write(cmdBuff[i]);
    Serial.print(cmdBuff[i], HEX);
    Serial.print(',');
  }
  Serial.println();
}

void loop()
{
    Serial.println("Going to sleep...");
    /* Re-enter sleep mode. */
    enterSleep();

    // An interrupt on Pin D2 should wake this up.
    detachInterrupt(digitalPinToInterrupt(pirInterrupt));
 
  
  // Only if the PIR is activated do we play the tune:
  // This code will just wake up if the PIR is activated
  // If PIR is triggered then it will play a random bird sample.
  // Otherwise it just goes to sleep again
    Serial.println("PIR TRIGGERED");
    Serial.println("Awake!");
    digitalWrite(powerControl, HIGH);
    digitalWrite(led, HIGH);
    for (int i = 0; i <= 100; i++)
    {
      delay(10);
    }
        
    // Randomly decide on the next tune:
    Serial.print("Next Track:");
    tune = random(tuneMax);
    
    tune = 5;
    Serial.println(tune);
    for(int j = 0; j<=tune; j++)
    {
      Serial.println(j);
      sendCommand(cmdNextTrack, 0);
      delay(1);
    }
      
//    // SHORT DELAY FOR TESTING
//    
   for(int i=0;i<200;i++)
   {
      sensorValue = analogRead(tuneBusy);
      delay(10);
   }  
    
    // Wait until track finished
    while(sensorValue<=400) // Busy signal is ACTIVE LOW
    {
//      Serial.println(analogRead(tuneBusy));
//      Serial.println("BUSY");
      for(int i=0;i<=10;i++)
      {
        delay(10);
      }
      sensorValue = analogRead(tuneBusy);
    }

    // Switch OFF power
    digitalWrite(powerControl, LOW);
    for (int i = 0; i <= 200; i++)
    {
      delay(10);
    }
    digitalWrite(led, LOW);             // MP3 module busy signal is active low.  
}


