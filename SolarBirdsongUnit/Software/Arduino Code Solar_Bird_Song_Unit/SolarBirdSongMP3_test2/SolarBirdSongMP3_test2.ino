// MP3 Module from http://www.embeddedadventures.com/soundout_mp3_module_mod-1021.html
// Player software & supporting hardware (c) 2014 vwlowen.co.uk 


#include <SoftwareSerial.h>z
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

#define powerControl  3

int savedVolume = 0;                        // EEPROM locations for saving current volume 
int savedEq = 2;                            // and equalizer values.

boolean changed = true;                     // Don't write EEPROM if value hasn't changed.

//int pinRepeatPlay = 8;                      // Define pins for 5-way navigation switch.
//int pinVolDown =  5;
//int pinVolUp = 6;
//int pinPrev = 9;
//int pinNext =  7;
//int pinEq =  10;                            // Equalizer select button.


int pinLED = 13;                            // Busy LED for ATTiny84;
//int pinBusy = A0;                            // Busy signal from MP3 module.

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
  pinMode(pinLED, OUTPUT);                      // Busy LED.  Echo the module Busy signal.
  
  mp3.begin(9600);                              // Initialise software serial.
  delay(150);
  sendCommand(cmdReset, 1);                    // Reset MP3 module (command, parameter).

  // Get last volume & equalizer values from EEPROM. Values will be wrong the very first
  // time power is applied so keep them within sane limits.  
  
//  volume = EEPROM.read(savedVolume);            // Only read Lo byte. Hi byte is always 0x00.
//  if (volume > 31) volume = 10;
//  eq = constrain(EEPROM.read(savedEq), 0, 5);   // Only read Lo byte. Hi byte is always 0x00.
// 
//   sendCommand(cmdReset, 1);                     // Reset MP3 module (command, parameter).
   delay(150);      
   sendCommand(cmdNextTrack, 0);
   for(int i=0;i<500;i++)
   {
    sensorValue = analogRead(tuneBusy);
    delay(10);
    Serial.println(sensorValue);
   }    
   mp3.end(); 
   delay(100);  
  
  
  
  mp3.end();  


  
  digitalWrite(pinLED, LOW);             // MP3 module busy signal is active low.
  digitalWrite(powerControl, LOW);
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

void restoreSaved() {
  sendCommand(cmdSetVolume, volume);                       // Set last volume.
  delay(100);
  sendCommand(cmdSetEq, eq);                               // Set last equalizer vaule.
  delay(100);  
}


// Loop through checking for a button-presses.
void loop() {
  
   digitalWrite(powerControl, HIGH);
   digitalWrite(pinLED, HIGH);  
   delay(1000);
   SoftwareSerial mp3(rxPin, txPin);           // Create software serial for MP3 module.
   delay(150);
   mp3.begin(9600); 
   delay(150);
   sendCommand(cmdReset, 1);                     // Reset MP3 module (command, parameter).
   delay(150);      
   sendCommand(cmdNextTrack, 0);
   for(int i=0;i<500;i++)
   {
    sensorValue = analogRead(tuneBusy);
    delay(10);
    Serial.println(sensorValue);
   }    
   mp3.end(); 
   delay(100);
   digitalWrite(powerControl, LOW);
   digitalWrite(pinLED, LOW);   
   delay(2000);
}  

