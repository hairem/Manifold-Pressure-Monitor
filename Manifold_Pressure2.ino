/*
 * SJVAPCD Manifold Pressure Sensor
 * With Serial Polling
 */

//Libraries used:
#include <Adafruit_MPRLS.h>
#include <Wire.h>
#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>

//Define Variables:
char inByte;
char INByte;
#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin
Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

BMx280I2C bmx280(0x76);
float Press;

void setup() {
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (! mpr.begin()) {
    Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
    while (1) {
      delay(10);
    }
  }
  Wire.begin();
  bmx280.begin();
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

  Serial.println("Found MPRLS sensor");
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    bmx280.measure();
    // get incoming byte:
    inByte = Serial.read();
        switch (inByte) {
      case 'a':
        Serial.print(mpr.readPressure()*0.4014631332);Serial.print(","); Serial.println("  Absolute Pressure inH20");
        break;
      case 'g':
        Press = mpr.readPressure()- ((bmx280.getPressure64()/100)-405.49);
        Serial.print(Press*0.4014631332,4);Serial.print(","); Serial.println("  Gauge Pressure inH20");
        break;
      case 'p':
        Serial.print(mpr.readPressure()/68.95,4);Serial.print(","); Serial.println("  Absolute Pressure PSIA");
        break;
      case 's':
        Press = mpr.readPressure()- ((bmx280.getPressure64()/100)-405.49);
        Serial.print(Press/68.95,4);Serial.print(",");Serial.println("  Guage Pressure PSI");
        break;
      case 'm':
        Serial.print((mpr.readPressure()/1.33322,4));Serial.print(","); Serial.println("  Absolute Pressure mmHg");
        break;
      case 'h':
        Press = mpr.readPressure()- ((bmx280.getPressure64()/100)-405.49);
        Serial.print(Press/1.3332,4);Serial.print(","); Serial.println("  Guage Pressure mmHg");
        break;
      case 'c':
        calibration();
        break;
      case 'd':
        Serial.print((bmx280.getPressure64()/100)-405.49);Serial.print(",");Serial.println(mpr.readPressure());
        break;
      case '?':
        Serial.println(" a = Absolute Pressure inH20");
        Serial.println(" g = Gauge Pressure inH20");
        Serial.println(" p = Absolute Pressure PSIA");
        Serial.println(" s = Guage Pressure PSI");
        Serial.println(" m = Absolute Pressure mmHg");
        Serial.println(" h = Guage Pressure mmHg");
        Serial.println(" c = Calibration Mode");
        break;
        }
}}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("Connection Comfirmed Awaiting Input. For Help enter ?");// send an initial string
    delay(300);
  }}
void calibration(){
  Serial.println(" Calibrations must be preformed using and absolute pressure standard.");
  Serial.println(" Do you want to (c)hange the calibration slope and intercept or (r)ead the current slope and intercept without changes?");
  INByte = Serial.read();
        switch (inByte) {
          case 'r':
            //read in slope and intercept values that were retrieved in setup 
            break;
    }
  }
