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

int REDLED = 7;
int YELLOWLED = 2;

int ANALOG_X = 0;
int ANALOG_Y = 1;
int ANALOG_Z = 2;

// Millis for light to stay on
int RED_DURATION= 10;
unsigned long red_light_start = 0;

int min_value = 1024;
int max_value = 0;

int vertical_stack[10];


void setup()
{
  for (unsigned int x=0; x< sizeof(vertical_stack); x++) {
    vertical_stack[x]=0;
  }  
  Serial.begin(9600);
  // Setup pin to be output
  pinMode(REDLED,OUTPUT);
  pinMode(YELLOWLED,OUTPUT);

}

int vertical_direction(int vertical_read) {
  return 0;
}

int last_read = 0;

int load_stats(int read_value, int motion_value, int min_value, int max_value,int light_value) {
  int variation = last_read * .01; 
  if (read_value > last_read + variation || read_value < last_read - variation) {
    Serial.print(millis(),DEC);
    Serial.print(",");
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
    last_read = read_value;
  }
}

void loop()
{
  int red_light = 0;
  analogRead(ANALOG_X);
  int vertical_read = analogRead(ANALOG_Y);
  int vertical_motion = vertical_direction(vertical_read);
  analogRead(ANALOG_Z);
  if (vertical_read > max_value) {
    max_value = vertical_read;
  }
  if (vertical_read < min_value) {
    min_value = vertical_read;
  }

  if (millis() - red_light_start < 1000) {
    red_light = 1;
    digitalWrite(REDLED, HIGH);
  } 
  else { 
    red_light = 0;
    digitalWrite(REDLED, LOW);
  }

  load_stats(vertical_read,vertical_motion, min_value, max_value,red_light);
  delay(100);
}



