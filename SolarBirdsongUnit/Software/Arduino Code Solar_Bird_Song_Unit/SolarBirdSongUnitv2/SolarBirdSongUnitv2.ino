/*
  The code for a Solar Powered Birdsong Unit
  This is recharged by solar PV power
  It has a PIR which sets off birdsong stored onto 
  an embedded adventures MOD1007 unit in ad4 format (!)
  The power to the sound unit and amplifier are controlled 
  using a digital output pin.

  This example code is in the public domain.
*/

/*
  Updates:
  5/5/15  First version of the code - Matt Little
  
*/

#include <avr/sleep.h>
#include <avr/power.h> 
 
 
// ***** Digital I/O *********
#define powerControl  5
#define pir 2
#define led 13

// Sound Module Connections  
#define RST 9    // change - pin 11
#define CLK 11    // " 12
#define SDATA 10 // " 13


// ******* Analogue I/O **********
int tuneBusy = A0;  // Measure when the audio module has finnished.


unsigned long tune = 0x0000;  // This is the tune file to play
unsigned long tuneMin = 0;  // This is the minimum tune ID
unsigned long tuneMax = 2;  // This is the maximum tune ID
unsigned long tunePlay = 0x0000;  //This holds the random tune ID
unsigned long testPlay = 0x0001;  //This holds the random tune ID

int sensorValue = 0;  // Holds the busy pin sensor value.

boolean busyPin = 0;  // This is a flag for the busyPin
boolean retrigger = HIGH;  // This stops the PIR triggering all the time.

void setup() 
{                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(pir, INPUT); 
  pinMode(powerControl, OUTPUT);
  pinMode(led, OUTPUT);
  
  pinMode(RST, OUTPUT);     // set pin to output
  pinMode(CLK, OUTPUT);     // set pin to output
  pinMode(SDATA, OUTPUT);     // set pin to output
  
  // initialise the outputs
  digitalWrite(RST, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SDATA, LOW);
  
  Serial.begin(9600);

  randomSeed(analogRead(0));
  tunePlay = (random(tuneMax-tuneMin))+tuneMin;  // Choose a song to play
  Serial.print("Random tune is:");
  Serial.println(tunePlay);

}

void loop() 
{
    // This code will just wake up, check the PIR
    // If PIR is triggered then it will play a random bird sample.
    // Otherwise it just goes to sleep again
   
    // Check the PIR here

    if(digitalRead(pir)==HIGH)
    {
      if(retrigger==HIGH)
      {
        // if the PIR has been triggered we set the LED high
        digitalWrite(led, HIGH);
        digitalWrite(powerControl, HIGH);
        delay(200);
        playTune(0xFFF7);  // 0xFFF0 = mute, 0xFFF7 = loud
        delay(100);  // Wait a bit       
        // We enter here is the timer has hit our playtime
        playTune(tunePlay);  
        //playTune(testPlay); 
        delay(200);
        digitalWrite(powerControl, LOW); 
        tunePlay = (random(tuneMax-tuneMin))+tuneMin;  // Choose a song to play
        Serial.print("Random tune is:");
        Serial.println(tunePlay);
      } 
      retrigger=LOW;
    }
    else
    {
      // Set the LED low
      digitalWrite(led,LOW);
      retrigger=HIGH;  // Allow another trigger to happen
    }
    
    delay(500);  
}

/***************************************************
 *  Name:        playTune
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  tune (a long int containing the file to play)
 *
 *  Description: Sets the sound module to play an output sound
 *
 ***************************************************/
 
void playTune(unsigned long tune)
{
   // The unit needs to be reset before sending commands
  // Reset means pull the line low for 5m then wait for >300mS
  digitalWrite(CLK, HIGH);
  delay(5);  // Wait a bit
  digitalWrite(RST, LOW);
  delay(5);  // Wait >5mS
  digitalWrite(RST, HIGH);
  delay(300);  // Wait >300mS  
  digitalWrite(CLK, LOW);  
  delay(3);  // Wait >2mS    
  // Here we start to clock in the data
  // Want to play track 1 (send the number 0x0000)
  // This is a 16 bit binary number
  // It would be best to have a function that you can send a 16 bit number to and it will paly the song
  // So lets have a long which holds the number
  Serial.print(tune,HEX);
  Serial.println(".ad4"); 
  for(int t=0; t<=15; t++)
  {
    // We read each bit in the long data file
    // If it is high then set the SData line high
    // We want to read out the MSB first
    digitalWrite(SDATA, bitRead(tune,(15-t)));  
    Serial.print(bitRead(tune,(15-t)));
    // Then we need to clock through the data
    digitalWrite(CLK, HIGH);  
    delayMicroseconds(80);   // Clock pulses should be >50uS 
    digitalWrite(CLK, LOW);
    delayMicroseconds(80);   // Clock pulses should be >50uS 
  }
  Serial.println();
  
  delay(500);
  sensorValue = analogRead(tuneBusy);
  Serial.println(analogRead(tuneBusy));
      
  while(sensorValue>=500)
  {
     //Serial.println(analogRead(tuneBusy));
     Serial.println("BUSY");
     delay(100);  // Wait a while
     sensorValue = analogRead(tuneBusy);
     //Serial.println(analogRead(tuneBusy));
  }
}
