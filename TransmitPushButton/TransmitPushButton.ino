/* YourDuinoStarter Example: nRF24L01 Transmit Joystick values
 - WHAT IT DOES: Reads push button changes and transmits value
   over a nRF24L01 Radio Link to another transceiver.
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED

 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[1];  // 2 element array holding Joystick readings
int pushPin = 2;
bool lastButton = LOW;
bool currentButton = LOW;
bool ledOn = false;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(pushPin, INPUT);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH)
  {
    ledOn = !ledOn;
  }
  lastButton = currentButton;
  if (ledOn) joystick[0] = 0;
  else joystick[0] = 1;
  radio.write( joystick, sizeof(joystick) );
  Serial.print(joystick[0]);
}//--(end main loop )---

/***** Debounce makes push button readings not bounce *****/
boolean debounce(boolean last)
{
  boolean current = digitalRead(pushPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pushPin);
  }
  return current;
}

//*********( THE END )***********
