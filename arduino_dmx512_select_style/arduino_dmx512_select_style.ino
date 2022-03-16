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

#define SW_INPUT 12

int ledState = LOW;
enum designFlags {
  STYLE_1,   
  STYLE_2,
  STYLE_3,
  
  START,
  COLOR_COUNT,
  DELAY_1000,
  DELAY_250,
  DELAY_X,
  
  END_FLAG
};

int styleState = STYLE_1;
int styleStateSub = START;
int delayCount = 0;
bool swPush = false;

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

//int state = 0;

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;

//int numRegisters = 3;
int numRGBleds = 8; //numRegisters*8/3;
int ledCount = 0;
int colorCount=0;
const unsigned char COLOR[][3] = { 
//  {255,255,255}, //white
//  {0,255,0}, //red
//  {127,255,0}, //orange 
//  {255,255,0}, //yellow 
//  {255,0,0}, //green
//  {0,0,255}, //blue
//  {0,75,130}, //indigo
//  {0,148,211}, //violet  

  {255,255,255}, //white
  {255,0,0}, //red
  {255,127,0}, //orange 
  {255,255,0}, //yellow 
  {0,255,0}, //green
  {0,0,255}, //blue
  {75,0,130}, //indigo
  {148,0,211}, //violet  
  };

//const unsigned char C_black[3] = {0,0,0};
//const unsigned char C_white[3] = {255,255,255};
//
//const unsigned char C_red[3] = {255,0,0};
//const unsigned char C_green[3] = {0,255,0};
//const unsigned char C_blue[3] = {0,0,255};
//
//const unsigned char C_orange[3] = {255,127,0};
//const unsigned char C_yellow[3] = {255,255,0};
//const unsigned char C_indigo[3] = {75,0,130};
//const unsigned char C_violet[3] = {148,0,211};
//
//const unsigned char C_cyan[3] = {0,255,255}; //ฟ้า
//const unsigned char C_magenta[3] = {255,0,255}; //ม่วง

#define C_black {0,0,0}
#define C_white {255,255,255}

#define C_red {255,0,0}
#define C_green {0,255,0}
#define C_blue {0,0,255}

#define C_orange {255,127,0}
#define C_yellow {255,255,0}
#define C_indigo {75,0,130}
#define C_violet {148,0,211}

#define C_cyan {0,255,255} //ฟ้า
#define C_magenta {255,0,255} //ม่วง

const unsigned char pattern2[][8][3] PROGMEM = {
//  { C_black, C_black, C_black, C_black, C_black, C_black, C_black, C_black }, 
  
  { C_black, C_red, C_red, C_red, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_red, C_red, C_red, C_black, C_black, C_black },  
  { C_black, C_black, C_black, C_red, C_red, C_red, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_red, C_red, C_red, C_black },  
  
  { C_yellow, C_black, C_black, C_black, C_black, C_red, C_red, C_red },
  { C_yellow, C_yellow, C_black, C_black, C_black, C_black, C_red, C_red },
  { C_yellow, C_yellow, C_yellow, C_black, C_black, C_black, C_black, C_red }, 

   
  { C_black, C_yellow, C_yellow, C_yellow, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_yellow, C_yellow, C_yellow, C_black, C_black, C_black },
  { C_black, C_black, C_black, C_yellow, C_yellow, C_yellow, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_yellow, C_yellow, C_yellow, C_black }, 
   
  { C_green, C_black, C_black, C_black, C_black, C_yellow, C_yellow, C_yellow },
  { C_green, C_green, C_black, C_black, C_black, C_black, C_yellow, C_yellow },
  { C_green, C_green, C_green, C_black, C_black, C_black, C_black, C_yellow },

    
  { C_black, C_green, C_green, C_green, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_green, C_green, C_green, C_black, C_black, C_black },  
  { C_black, C_black, C_black, C_green, C_green, C_green, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_green, C_green, C_green, C_black },
  
  { C_cyan, C_black, C_black, C_black, C_black, C_green, C_green, C_green },
  { C_cyan, C_cyan, C_black, C_black, C_black, C_black, C_green, C_green },
  { C_cyan, C_cyan, C_cyan, C_black, C_black, C_black, C_black, C_green },  

  
  { C_black, C_cyan, C_cyan, C_cyan, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_cyan, C_cyan, C_cyan, C_black, C_black, C_black },
  { C_black, C_black, C_black, C_cyan, C_cyan, C_cyan, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_cyan, C_cyan, C_cyan, C_black },
  
  { C_magenta, C_black, C_black, C_black, C_black, C_cyan, C_cyan, C_cyan },
  { C_magenta, C_magenta, C_black, C_black, C_black, C_black, C_cyan, C_cyan },
  { C_magenta, C_magenta, C_magenta, C_black, C_black, C_black, C_black, C_cyan },


  { C_black, C_magenta, C_magenta, C_magenta, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_magenta, C_magenta, C_magenta, C_black, C_black, C_black },
  { C_black, C_black, C_black, C_magenta, C_magenta, C_magenta, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_magenta, C_magenta, C_magenta, C_black },
  
  { C_blue, C_black, C_black, C_black, C_black, C_magenta, C_magenta, C_magenta },
  { C_blue, C_blue, C_black, C_black, C_black, C_black, C_magenta, C_magenta },
  { C_blue, C_blue, C_blue, C_black, C_black, C_black, C_black, C_magenta },


  { C_black, C_blue, C_blue, C_blue, C_black, C_black, C_black, C_black },
  { C_black, C_black, C_blue, C_blue, C_blue, C_black, C_black, C_black },
  { C_black, C_black, C_black, C_blue, C_blue, C_blue, C_black, C_black },
  { C_black, C_black, C_black, C_black, C_blue, C_blue, C_blue, C_black },

  { C_red, C_black, C_black, C_black, C_black, C_blue, C_blue, C_blue },
  { C_red, C_red, C_black, C_black, C_black, C_black, C_blue, C_blue },
  { C_red, C_red, C_red, C_black, C_black, C_black, C_black, C_blue }  

};

const unsigned char pattern3[][8][3] PROGMEM = {
//  { C_black, C_black, C_black, C_black, C_black, C_black, C_black, C_black }, 
  { C_white, C_white, C_black, C_black, C_white, C_white, C_black, C_black },
  { C_black, C_white, C_white, C_black, C_black, C_white, C_white, C_black },
  { C_black, C_black, C_red, C_red, C_black, C_black, C_red, C_red },
  { C_red, C_black, C_black, C_red, C_red, C_black, C_black, C_red },
  { C_black, C_green, C_green, C_black, C_black, C_green, C_green, C_black },
  { C_black, C_black, C_green, C_green, C_black, C_black, C_green, C_green },  
  { C_blue, C_black, C_black, C_blue, C_blue, C_black, C_black, C_blue },
  { C_blue, C_blue, C_black, C_black, C_blue, C_blue, C_black, C_black },
  
  { C_black, C_yellow, C_yellow, C_black, C_black, C_yellow, C_yellow, C_black },
  { C_black, C_black, C_yellow, C_yellow, C_black, C_black, C_yellow, C_yellow },
  { C_indigo, C_black, C_black, C_indigo, C_indigo, C_black, C_black, C_indigo },
  { C_indigo, C_indigo, C_black, C_black, C_indigo, C_indigo, C_black, C_black },
  { C_black, C_cyan, C_cyan, C_black, C_black, C_cyan, C_cyan, C_black },
  { C_black, C_black, C_cyan, C_cyan, C_black, C_black, C_cyan, C_cyan },
  { C_magenta, C_black, C_black, C_magenta, C_magenta, C_black, C_black, C_magenta },
  { C_magenta, C_magenta, C_black, C_black, C_magenta, C_magenta, C_black, C_black },

  { C_black, C_orange, C_orange, C_black, C_black, C_orange, C_orange, C_black },
  { C_black, C_black, C_orange, C_orange, C_black, C_black, C_orange, C_orange },

  { C_violet, C_black, C_black, C_violet, C_violet, C_black, C_black, C_violet }
 
};

void setup() {
  DMXSerial.init(DMXController); //use
//  DMXSerial.maxChannel(24);
  
  pinMode(RedPin,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin,  OUTPUT);

  pinMode(SW_INPUT, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
//  Serial.begin(115200); //tesr

} // setup

void loop() {
//  colorCount=1;
//  ledCount=0;
  int swState = digitalRead(SW_INPUT);
  if(!swState) {
    swPush = true;
    digitalWrite(LED_BUILTIN, 1); //on
  } 
  else {
    if(swPush) {
      digitalWrite(LED_BUILTIN, 0); //off
      
      swPush = false;
      if(styleState == STYLE_1) styleState = STYLE_2;
      else if(styleState == STYLE_2) styleState = STYLE_3;
      else styleState = STYLE_1;  
          
      styleStateSub = START;    
      ledCount = 0;
      colorCount = 0;
//      Serial.println();
//      Serial.println("------------------");
//      Serial.print("styleState: ");
//      Serial.println(styleState);
      delay(1000);
    }
  }  
//  styleState = STYLE_1;
  
  switch(styleState) {
    case STYLE_1:
      style1();
    break;

    case STYLE_2:
      style2();
    break;

    case STYLE_3:
      style3();
    break;
    
  }
}

void style1() {
//  styleStateSub = STYLE_1_START;
  switch(styleStateSub) {
    case START: 
//      Serial.println("");
//      Serial.print(ledCount);
//      Serial.print("|");
      
      DMXSerial.write(ledCount+1, COLOR[colorCount][0]); //green
//      analogWrite(RedPin, ~COLOR[colorCount][0]); 
//      Serial.print( COLOR[colorCount][0] );
//      Serial.print(",");
        
      DMXSerial.write(ledCount+2, COLOR[colorCount][1]); //red
//      analogWrite(GreenPin, ~COLOR[colorCount][1]);  
//      Serial.print( COLOR[colorCount][1] );
//      Serial.print(",");
    
      DMXSerial.write(ledCount+3, COLOR[colorCount][2]); //blue
//      analogWrite(BluePin,  ~COLOR[colorCount][2]); 
//      Serial.print( COLOR[colorCount][2] );
//      Serial.print(",");

      ledCount += 3;
      if(ledCount/3 >= numRGBleds) {
        ledCount = 0;
//        delay(1000);
        delayCount = 1000;
        styleStateSub = DELAY_1000;
        //Serial.println("-");
        return;
//        if(++colorCount >= sizeof(COLOR)/3) {
//          colorCount = 0;
//        }
      }
//      delay(250); 
      delayCount = 250;
      styleStateSub = DELAY_250;
      
    break;

    case DELAY_250:
      delay(1);
      if(--delayCount <= 0) styleStateSub = START;
    break;

    case DELAY_1000:
      delay(1);
      if(--delayCount <= 0) styleStateSub = COLOR_COUNT;
    break;

    case COLOR_COUNT:
      if(++colorCount >= sizeof(COLOR)/3) {
        colorCount = 0;
      }
      styleStateSub = START;
//      Serial.print("x");
//      Serial.println(colorCount);
    break;
       
  }
}

void style2() {
  switch(styleStateSub) {
    case START: 
      //Serial.print("ledCount: ");
      for(int i=0; i<DMXSERIAL_MAX/3; i++) {
        DMXSerial.write(ledCount+1, pgm_read_byte(&pattern2[colorCount][i][0]) ); //red 
        //Serial.print(ledCount+1);
//        Serial.print( pgm_read_byte(&pattern2[colorCount][i][0]) );
//        Serial.print(",");
        
        DMXSerial.write(ledCount+2, pgm_read_byte(&pattern2[colorCount][i][1]) ); //green
        //Serial.print(ledCount+2);
//        Serial.print( pgm_read_byte(&pattern2[colorCount][i][1]) );
//        Serial.print(",");
        
        DMXSerial.write(ledCount+3, pgm_read_byte(&pattern2[colorCount][i][2]) ); //blue        
        //Serial.print(ledCount+3);
//        Serial.print( pgm_read_byte(&pattern2[colorCount][i][2]) );
//        Serial.print("|");
        ledCount += 3;
      }      
      //Serial.println();
      ledCount = 0;
      delayCount = 400;
      styleStateSub = DELAY_X;
      
    break;

    case DELAY_X:
      delay(1);
      if(--delayCount <= 0) styleStateSub = COLOR_COUNT;
    break;

    case COLOR_COUNT:
      if(++colorCount >= sizeof(pattern2)/(8*3) ) {
        colorCount = 0;
      }
      styleStateSub = START;
//      Serial.print("colorCount:");
//      Serial.println(colorCount);
    break;
       
  }
}

void style3() {
  switch(styleStateSub) {
    case START: 
      //Serial.print("ledCount: ");
      for(int i=0; i<DMXSERIAL_MAX/3; i++) {
        DMXSerial.write(ledCount+1, pattern3[colorCount][i][0]); //red 
        //Serial.print(ledCount+1);
//        Serial.print( pgm_read_byte(&pattern3[colorCount][i][0]) );
//        Serial.print(",");
        
        DMXSerial.write(ledCount+2, pattern3[colorCount][i][1]); //green
        //Serial.print(ledCount+2);
//        Serial.print( pgm_read_byte(&pattern3[colorCount][i][1]) );
//        Serial.print(",");
        
        DMXSerial.write(ledCount+3, pattern3[colorCount][i][2]); //blue        
        //Serial.print(ledCount+3);
//        Serial.print( pgm_read_byte(&pattern3[colorCount][i][2]) );
//        Serial.print("|");
        ledCount += 3;
      }      
      //Serial.println();
      ledCount = 0;
      delayCount = 400;
      styleStateSub = DELAY_X;
      
    break;

    case DELAY_X:
      delay(1);
      if(--delayCount <= 0) styleStateSub = COLOR_COUNT;
    break;

    case COLOR_COUNT:
      if(++colorCount >= sizeof(pattern3)/(8*3) ) {
        colorCount = 0;
      }
      styleStateSub = START;
//      Serial.print("colorCount:");
//      Serial.println(colorCount);
    break;
       
  }
}
