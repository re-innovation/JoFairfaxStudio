// MP3 Module from http://www.embeddedadventures.com/soundout_mp3_module_mod-1021.html
// Player software & supporting hardware (c) 2014 vwlowen.co.uk 

#include <stdlib.h>
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h> 
#include <avr/wdt.h> 
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define rxPin 10                             // Software Serial Rx from MP3 Module Tx pin.
#define txPin 11                            // Software Serial Tx to MP3 Module Rx pin.

// Define the MP3 Module's Commands that we'll be using
#define cmdNextTrack  0x01                  // Next track.      
#define cmdPrevTrack  0x02                  // Previous track.
#define cmdRepeatPlay 0x11                  // Repeat play.

#define cmdSetVolume  0x06                  // Set Volume to a specified value.
#define cmdSetEq      0x07                  // Set Equalizer to a specified value.
#define cmdReset      0x0c                  // Reset MP3 Module.

#define powerControl  5

int savedVolume = 0;                        // EEPROM locations for saving current volume 
int savedEq = 2;                            // and equalizer values.

volatile int f_wdt=1;

boolean changed = true;                     // Don't write EEPROM if value hasn't changed.

//int pinRepeatPlay = 8;                      // Define pins for 5-way navigation switch.
//int pinVolDown =  5;
//int pinVolUp = 6;
//int pinPrev = 9;
//int pinNext =  7;
//int pinEq =  10;                            // Equalizer select button.


int pinLED = 2;                            // Busy LED for ATTiny84;
int pinBusy = 3;                            // Busy signal from MP3 module.

SoftwareSerial mp3(rxPin, txPin);           // Create software serial for MP3 module.

unsigned int volume = 10;                   // Starting MP3 module volume (0 - 31).
unsigned int eq = 0;                        // Normal/Pop/Rock/Jazz/Classic/Base equalizer.

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
                    
int tuneBusy = A0;  // Measure when the audio module has finnished.                    
int sensorValue = 0;  // Holds the busy pin sensor value.

/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
    //Serial.println("WDT");
  }
  else
  {
    // Should never get here
    // Always need to "pat the dog" every 0.5s
    Serial.println("WDT Overrun!!!");
  }
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
  sleep_enable();
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    
    
  byte old_ADCSRA = ADCSRA;  // Store the old value to re-enable
  
  // disable ADC
  ADCSRA = 0;
  
  byte old_PRR = PRR;  // Store previous version on PRR
  // turn off various modules
  PRR = 0b11111111;
  
  // clear various "reset" flags
  // MCUSR = 0;    
  
  sleep_cpu();
  
  /* The program will continue from here. */
  /************* ASLEEP *******************/
  
  // ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ //
  
  /************** WOKEN UP ***************/
  /* First thing to do is disable sleep. */
  sleep_disable();
  // turn ON various modules USART and ADC
  PRR = old_PRR;  
  // enable ADC
  ADCSRA = old_ADCSRA;  
}

                    
void setup() {

  pinMode(powerControl, OUTPUT);
  digitalWrite(powerControl, HIGH);
  
//  pinMode(pinRepeatPlay, INPUT_PULLUP);             // Set button pins as inputs and
//                                                    // enable internal pullups.
//  //pinMode(pinVolDown, INPUT_PULLUP);
//  pinMode(pinVolUp, INPUT_PULLUP);
//  pinMode(pinEq, INPUT_PULLUP);
//  pinMode(pinPrev, INPUT_PULLUP);
//  pinMode(pinNext, INPUT_PULLUP);

  Serial.begin(9600); 
  pinMode(pinBusy, INPUT);                      // Input from MP3 module. No pullup needed.
  pinMode(pinLED, OUTPUT);                      // Busy LED.  Echo the module Busy signal.
  
  mp3.begin(9600);                              // Initialise software serial.
  delay(150);
  sendCommand(cmdReset, 1);                     // Reset MP3 module (command, parameter).
  //delay(5000);
  digitalWrite(pinLED, HIGH);             // MP3 module busy signal is active low.
  digitalWrite(powerControl, LOW);

     /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP2; /* 0.5 seconds */
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  delay(10);
}


// Loop through checking for a button-presses.
void loop() {
   enterSleep();
   delay(10);
   Serial.println("Awake!"); 
   digitalWrite(powerControl, HIGH);
    for(int i=0;i<=500;i++)
    {
      f_wdt = 0;  // Service the WDT
      delay(10);
    }  
   Serial.println("Next Track");
   sendCommand(cmdNextTrack, 0);
   for(int i=0;i<1000;i++)
   {
    sensorValue = analogRead(tuneBusy);
    delay(10);
     f_wdt = 0;  // Service the WDT
    //Serial.println(sensorValue);
   }    
   digitalWrite(powerControl, LOW);
    for(int i=0;i<=500;i++)
    {
      f_wdt = 0;  // Service the WDT
      delay(10);
    }     
}  

// Routine to build 10-byte command buffer and write to software serial Tx (MP3 module Rx).
void sendCommand(byte Cmd, unsigned int Param) {
  unsigned int sum = 0;
  
  cmdBuff[3] = Cmd;                    // Command.
  cmdBuff[5] = (byte) (Param >> 8);    // Param Hi byte.
  cmdBuff[6] = (byte) (Param);         // Param Lo byte. 
  
  for (int i=1; i<7; i++) {            // Calculate 16-bit checksum from buffer bytes 1 to 6.
    sum -= cmdBuff[i];
  }
 
  cmdBuff[7] = (byte) (sum >> 8);      // Add checksum Hi byte to buffer.
  cmdBuff[8] = (byte) sum;             // Add checksum Lo byte to buffer.

  for (int i = 0; i<10; i++) {         // Write entire buffer to software serial (mp3).
    mp3.write(cmdBuff[i]);
  }      
}

