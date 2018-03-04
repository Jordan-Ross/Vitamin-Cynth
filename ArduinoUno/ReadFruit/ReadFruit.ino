/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#define MIN_ITERATIONS 15
#define SOUND_PIN 7

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t curtouchedcount = 0;

uint8_t RESET = 0b10000000;
uint8_t A = 0b01000000;
uint8_t B = 0b00100000;
uint8_t C = 0b00010000;
uint8_t D = 0b00001000;
uint8_t E = 0b00000100;
uint8_t F = 0b00000010;
uint8_t G = 0b00000001;

// Rough estimates
uint16_t C_period = 1600; //us
uint16_t Cs_period = 1500; //us
uint16_t D_period = 1400; //us
uint16_t Ds_period = 1310; //us
uint16_t E_period = 1220; //us
uint16_t F_period = 1140; //us
uint16_t Fs_period = 1050; //us
uint16_t G_period = 975; //us
uint16_t Gs_period = 900; //us
uint16_t A_period = 840; //us
uint16_t As_period = 780; //us
uint16_t B_period = 710; //us

uint16_t cur_delay_us = A_period;
int sound_on = 0;

void setup() {
  Serial.begin(9600);
  
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  pinMode(SOUND_PIN, OUTPUT);           // set pin to output
  
  //Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    //Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  //Serial.println("MPR121 found!");
  cap.setThresholds(30, 6);
}

void loop() {

  // Get the currently touched pads
  currtouched = cap.touched();
  
  //uint8_t activeNotes = B00000000;


  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched, increment count
    if ((currtouched & _BV(i))) {
      curtouchedcount++;
      lasttouched = currtouched;
    }
    // it if *is* touched and *wasnt* touched before, and curtouchedcount > MIN_ITERATIONS, alert!
    //if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
    if ((currtouched & _BV(i)) ) {
      if (curtouchedcount > MIN_ITERATIONS) {
        //Serial.print(i); Serial.println(" touched");
        sound_on = 1;
        switch (i) {
          case 0:
            cur_delay_us = C_period;
            break;
          case 1:
            cur_delay_us = Cs_period;
            break;
          case 2:
            cur_delay_us = D_period;
            break;
          case 3:
            cur_delay_us = Ds_period;
            break;
          case 4:
            cur_delay_us = E_period;
            break;
          case 5:
            cur_delay_us = F_period;
            break;
          case 6:
            cur_delay_us = Fs_period;
            break;
          case 7:
            cur_delay_us = G_period;
            break;
          case 8:
            cur_delay_us = Gs_period;
            break;
          case 9:
            cur_delay_us = A_period;
            break;
          case 10:
            cur_delay_us = As_period;
            break;
          case 11:
            cur_delay_us = B_period;
            break;
        }
         // reset our state
        //lasttouched = currtouched;
      }
      //Serial.println(curtouchedcount);
    }
    
    
    
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
      if (curtouchedcount > MIN_ITERATIONS) {
        //Serial.print(i); Serial.println(" released");
        sound_on = 0;
        /*
        switch (i) {
          //case 1:
          case 9: // Pin 9 because that's what's connected right now (lol)
            activeNotes &= !A;
            break;
          case 6:
            activeNotes &= !B;
            break;
          case 3:
            activeNotes &= !C;
            break;
          case 4:
            activeNotes &= !D;
            break;
          case 5:
            activeNotes &= !E;
            break;
          //case 6:
            activeNotes &= !F;
            break;
          case 7:
            activeNotes &= !G;
            break;
        }
        */
      }
      lasttouched = 0;
      curtouchedcount = 0;
    }


  }
  
  if (sound_on) digitalWrite(SOUND_PIN, HIGH);
  delayMicroseconds(cur_delay_us);
  if (sound_on) digitalWrite(SOUND_PIN, LOW);
  delayMicroseconds(cur_delay_us);
  
  return;
  
//  Serial.write(RESET);
//  Serial.write(activeNotes);
//  Serial.write(0);
//  Serial.write(0);



  //Serial.println(curtouchedcount);




  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);
}
