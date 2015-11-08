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
int pushPin1 = 2;
int pushPin2 = 3;
bool lastButton1 = LOW;
bool currentButton1 = LOW;
bool lastButton2 = LOW;
bool currentButton2 = LOW;
bool ledOn1 = false;
bool ledOn2 = false;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(pushPin1, INPUT);
  pinMode(pushPin2, INPUT);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  currentButton1 = debounce(lastButton1, pushPin1);
  if (lastButton1 == LOW && currentButton1 == HIGH)
  {
    ledOn1 = !ledOn1;
  }
  lastButton1 = currentButton1;
  
  if (ledOn1) joystick[0] = 0;
  else joystick[0] = 1;
  radio.write( joystick, sizeof(joystick) );
  Serial.print(joystick[0]);
  
  currentButton2 = debounce(lastButton2, pushPin2);
  if (lastButton2 == LOW && currentButton2 == HIGH)
  {
    ledOn2 = !ledOn2;
  }
  lastButton2 = currentButton2;
  
  if (ledOn2) joystick[0] = 2;
  else joystick[0] = 3;
  radio.write( joystick, sizeof(joystick) );
  Serial.print(joystick[0]);
}//--(end main loop )---

/***** Debounce makes push button readings not bounce *****/
boolean debounce(boolean last, int pushPin)
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
