/*
  The code for a Solar Powered Birdsong Unit
  This is recharged by solar PV power
  It has a PIR which sets off birdsong stored onto 
  an embedded adventures MOD1007 unit in ad4 format (!)
  The power to the sound unit and amplifier are controlled 
  using a digital output pin.

  This must have a decent power supply (eg. battery) or it will brown-out reset.
  
  This runs on a Pro-mini 5V
  It uses a Sound Module MOD-1007 from Embedded adventures. (change to SoundOut MP3 module)
  A li-po rider + PV module is used to recharge a 2000mAh li-ion battery
  A simple PIR sensor is used to trigger the unit.
  
  To reduce power consumption the unit goes to sleep a LOT.
  A WDT wakes it up every 0.5s to check on the PIR.
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

#include <avr/sleep.h>
#include <avr/power.h> 
#include <avr/wdt.h> 
 
// ***** Digital I/O *********
#define powerControl  5
#define pir 6
#define led 13

// Sound Module Connections  
#define RST 9    // change - pin 11
#define CLK 11    // " 12
#define SDATA 10 // " 13


// ******* Analogue I/O **********
int tuneBusy = A0;  // Measure when the audio module has finnished.

unsigned long tune = 0x0000;  // This is the tune file to play
unsigned long tuneMin = 2;  // This is the minimum tune ID (ususally 02)
unsigned long tuneMax = 23;  // This is the maximum tune ID (usually 23)
unsigned long tunePlay = 0x0000;  //This holds the random tune ID
unsigned long testPlay = 0x0001;  //This holds the random tune ID

int sensorValue = 0;  // Holds the busy pin sensor value.

boolean busyPin = 0;  // This is a flag for the busyPin
//boolean retrigger = HIGH;  // This stops the PIR triggering all the time.

volatile int f_wdt=1;

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
  
//  // clear various "reset" flags
//  MCUSR = 0;    
  
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

  randomSeed(analogRead(A3));  // Read a disconnected pin to seed the random algorithm
  tunePlay = (random(tuneMax-tuneMin))+tuneMin;  // Choose a song to play
  Serial.print("Random tune is:");
  Serial.println(tunePlay);
 
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
  delay(100);
  
  //attachInterrupt(PIRinterrupt, PIR, CHANGE); 
  //digitalWrite(powerControl, HIGH);
}

void loop() 
{
  if(f_wdt == 1)
  {
    
    /* Toggle the LED */
    // digitalWrite(led, !digitalRead(led));

    // Only if the PIR is activated do we play the tune:
    // This code will just wake up if the PIR is activated
    // If PIR is triggered then it will play a random bird sample.
    // Otherwise it just goes to sleep again
    if(digitalRead(pir)==HIGH)
    { 
      
      // if the PIR has been triggered we set the LED high
      digitalWrite(led, HIGH);
      digitalWrite(powerControl, HIGH);
      // The unit needs to be reset before sending commands
      for(int i=0;i<=50;i++)
      {
        f_wdt = 0;  // Service the WDT
        delay(10);
      }      
      playTune(0xFFF7);  // 0xFFF0 = mute, 0xFFF7 = loud
      for(int i=0;i<=50;i++)
      {
        f_wdt = 0;  // Service the WDT
        delay(10);
      }     
      // We enter here is the timer has hit our playtime
      playTune(tunePlay);  
      tunePlay = (random(tuneMax-tuneMin))+tuneMin;  // Choose a song to play
      Serial.print("Random tune is:");
      Serial.println(tunePlay); 
      for(int i=0;i<=200;i++)
      {
        f_wdt = 0;   // Service the WDT
        delay(10);
      }
      digitalWrite(powerControl, LOW); 
      
    }
    else
    {
      digitalWrite(led,LOW);    
    } 
    /* Don't forget to clear the flag. */
    f_wdt = 0;   // Service the WDT
    /* Re-enter sleep mode. */
    enterSleep(); 
  }
  else
  {
    /* Do nothing. */
    /* Don't forget to clear the flag. */
    f_wdt = 0;   // Service the WDT
    /* Re-enter sleep mode. */
    enterSleep();
  }
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
  delay(10);  // Wait a bit
  digitalWrite(RST, LOW);
  delay(10);  // Wait >5mS
  digitalWrite(RST, HIGH);
  for(int i=0;i<=35;i++)
  {
    f_wdt = 0;  // Service the WDT
    delay(10);
  }
  digitalWrite(CLK, LOW);  
  delay(4);  // Wait >2mS    
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
    delayMicroseconds(100);   // Clock pulses should be >50uS 
    digitalWrite(CLK, LOW);
    delayMicroseconds(100);   // Clock pulses should be >50uS 
  }
  Serial.println();
  
  for(int i=0;i<=50;i++)
  {
    f_wdt = 0;  // Service the WDT
    delay(10);
  }
  sensorValue = analogRead(tuneBusy);
      
  while(sensorValue>=400)
  {
     //Serial.println(analogRead(tuneBusy));
     Serial.println("BUSY");
    for(int i=0;i<=10;i++)
    {
      f_wdt = 0;  // Service the WDT
      delay(10);
    }
     sensorValue = analogRead(tuneBusy);
     //Serial.println(analogRead(tuneBusy));
  }
}
