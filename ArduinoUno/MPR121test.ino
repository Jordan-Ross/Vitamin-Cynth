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

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t curtouchedcount = 0;

// Setup output pins with notes
int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int F = 7;
int G = 8;

void setup() {
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  cap.setThresholds(30, 6);
}

void loop() {

  // Get the currently touched pads
  currtouched = cap.touched();

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
        Serial.print(i); Serial.println(" touched");
        switch (i) {
          //case 1:
          case 9: // Pin 9 because that's what's connected right now (lol)
            digitalWrite(A, HIGH);
            break;
          case 2:
            digitalWrite(B, HIGH);
            break;
          case 3:
            digitalWrite(C, HIGH);
            break;
          case 4:
            digitalWrite(D, HIGH);
            break;
          case 5:
            digitalWrite(E, HIGH);
            break;
          case 6:
            digitalWrite(F, HIGH);
            break;
          case 7:
            digitalWrite(G, HIGH);
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
        Serial.print(i); Serial.println(" released");
        switch (i) {
          //case 1:
          case 9: // Pin 9 because that's what's connected right now (lol)
            digitalWrite(A, LOW);
            break;
          case 2:
            digitalWrite(B, LOW);
            break;
          case 3:
            digitalWrite(C, LOW);
            break;
          case 4:
            digitalWrite(D, LOW);
            break;
          case 5:
            digitalWrite(E, LOW);
            break;
          case 6:
            digitalWrite(F, LOW);
            break;
          case 7:
            digitalWrite(G, LOW);
            break;
        }
      }
      lasttouched = 0;
      curtouchedcount = 0;
    }
  }



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
