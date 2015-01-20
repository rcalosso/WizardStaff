/* Pro Micro Test Code
 by: Nathan Seidle
 modified by: Jim Lindblom
 SparkFun Electronics
 date: September 16, 2013
 license: Public Domain - please use this code however you'd like.
 It's provided as a learning tool.
 
 This code is provided to show how to control the SparkFun
 ProMicro's TX and RX LEDs within a sketch. It also serves
 to explain the difference between Serial.print() and
 Serial1.print().
 */

#include "Vertical.h"

int REDLED = 7;
int RED_LIGHT_DURATION = 5 * 1000;

int ANALOG_X = 0;
int ANALOG_Y = 1;
int ANALOG_Z = 2;

int min_value = 1024;
int max_value = 0;

Vertical vertical(ANALOG_Y);

unsigned long red_light_end;

void setup()
{
  Serial.begin(9600);
  // Setup pin to be output
  pinMode(REDLED,OUTPUT);
  red_light_end = 0;
};

int load_stats(int read_value, int motion_value, int min_value, int max_value,int light_value) {
  //int variation = last_read * .01; 
  //if (read_value > last_read + variation || read_value < last_read - variation) {
  //Serial.print(millis(),DEC);
  //Serial.print(",");
  Serial.print(read_value,DEC);
  Serial.print(",");
  Serial.print(motion_value,DEC);
  Serial.print(",");
  Serial.print(min_value,DEC);
  Serial.print(",");
  Serial.print(max_value,DEC);
  Serial.print(",");
  Serial.print(light_value,DEC);
  Serial.println("");
  //last_read = read_value;
  //}
}

void loop()
{

  int vertical_read = vertical.read();
  int vertical_motion = vertical.motion();
  if (vertical_read > max_value) {
    max_value = vertical_read;
  }
  if (vertical_read < min_value) {
    min_value = vertical_read;
  }

  if (red_light_end == 0) {
    if (vertical.light()) {
      red_light_end = millis() + RED_LIGHT_DURATION;
      digitalWrite(REDLED, HIGH); 
    }
  } 
  else {
    if ((vertical.motion() != 0) || (red_light_end < millis()) ){
      digitalWrite(REDLED,LOW);
      red_light_end = 0;
    }
  }

  //load_stats(vertical_read,vertical_motion, min_value, max_value,(red_light_end > 0));
  delay(75);
}









