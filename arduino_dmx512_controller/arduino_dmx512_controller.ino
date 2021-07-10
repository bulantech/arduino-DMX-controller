// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialSend.ino: Sample DMX application for sending 3 DMX values.
// There colors in the 3 lists (RedList, GreenList and BlueList) are placed into the DMX buffer with a slow fade.
// DMXSerial works in the background and constantly sends the actual values over the DMX interface.
// The actual values are also available on the built in PWM ports:
// address 1 (red) -> also available on PWM Port 9
// address 2 (green) -> also available on PWM Port 6
// address 3 (blue) -> also available on PWM Port 5
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// The repository is on github : https://github.com/mathertel/DMXSerial
// The repository on github is made available in the Arduino Library Manager.
//
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// - - - - -

#define DMXSERIAL_MAX 24
#include <DMXSerial.h>

// Constants for demo program

const int RedPin =    9;  // PWM output pin for Red Light.
const int GreenPin =  6;  // PWM output pin for Green Light.
const int BluePin =   5;  // PWM output pin for Blue Light.

// The color fading pattern

int RedList[]   = {255, 128,   0,   0,   0, 128};
int GreenList[] = {  0, 128, 255, 128,   0,   0};
int BlueList[]  = {  0,   0,   0, 128, 255, 128};

int RedLevel, GreenLevel, BlueLevel;

int RedNow = 0;
int GreenNow = 0;
int BlueNow = 0;

int state = 0;

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;

//int numRegisters = 3;
int numRGBleds = 8; //numRegisters*8/3;
int ledCount=0;
int colorCount=0;
const unsigned char COLOR[][3] = { 
  {255,255,255}, //white
  {0,255,0}, //red
  {127,255,0}, //orange 
  {255,255,0}, //yellow 
  {255,0,0}, //green
  {0,0,255}, //blue
  {0,75,130}, //indigo
  {0,148,211}, //violet  
  };
  
void setup() {
  DMXSerial.init(DMXController);
//  DMXSerial.maxChannel(24);
  
  pinMode(RedPin,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin,  OUTPUT);
} // setup

void loop() {
//  colorCount=1;
//  ledCount=0;
  
  DMXSerial.write(ledCount+1, COLOR[colorCount][0]); //green
  analogWrite(RedPin, ~COLOR[colorCount][0]); 
  
  DMXSerial.write(ledCount+2, COLOR[colorCount][1]); //red
  analogWrite(GreenPin, ~COLOR[colorCount][1]);  

  DMXSerial.write(ledCount+3, COLOR[colorCount][2]); //blue
  analogWrite(BluePin,  ~COLOR[colorCount][2]); 

  ledCount += 3;
  if(ledCount/3 >= numRGBleds) {
    ledCount = 0;
    delay(1000);
    if(++colorCount >= sizeof(COLOR)/3) {
      colorCount = 0;
    }
  }
  
  delay(250);
}

 void loop2() {
  DMXSerial.write(1, 255); //green
  analogWrite(RedPin,   ~255); 
//  return;
  
  DMXSerial.write(2, 0); //red
  analogWrite(GreenPin, ~0);  

  DMXSerial.write(3, 0); //blue
  analogWrite(BluePin,  ~0); 

  delay(1000);

  DMXSerial.write(10, 0); //green
  analogWrite(RedPin,   ~0);  
  
  DMXSerial.write(11, 255); //red
  analogWrite(GreenPin, ~255);  

  DMXSerial.write(12, 0); //blue
  analogWrite(BluePin,  ~0); 

  delay(1000);

  DMXSerial.write(1, 0); //green
  analogWrite(RedPin,   ~0); 
  
  DMXSerial.write(2, 0); //red
  analogWrite(GreenPin, ~0);  

  DMXSerial.write(3, 255); //blue
  analogWrite(BluePin,  ~255); 

  delay(1000);
    
//  delayMicroseconds(2000); // wait a little bit
}

// loop through the rainbow colors 
void loop1() {
  RedLevel = RedList[state];
  GreenLevel = GreenList[state];
  BlueLevel = BlueList[state];
  
  if ((RedLevel == RedNow) && (GreenLevel == GreenNow) && (BlueLevel == BlueNow)) {
    state += 1;
    if (state == 6)
      state = 0;

  } else {
    if (RedNow < RedLevel)  RedNow++; 
    if (RedNow > RedLevel)  RedNow--; 
    DMXSerial.write(1, RedNow);
    analogWrite(RedPin,   RedNow); 

    if (GreenNow < GreenLevel)  GreenNow++; 
    if (GreenNow > GreenLevel)  GreenNow--; 
    DMXSerial.write(11, GreenNow);
    analogWrite(GreenPin, GreenNow); 

    if (BlueNow < BlueLevel)  BlueNow++; 
    if (BlueNow > BlueLevel)  BlueNow--; 
    DMXSerial.write(13, BlueNow);
    analogWrite(BluePin,  BlueNow); 
  } // if

  delayMicroseconds(5000); // wait a little bit
} // loop
