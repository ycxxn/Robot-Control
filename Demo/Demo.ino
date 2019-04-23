#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>


double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeLineFollower linefollower_2(2);
MeLineFollower linefollower_3(3);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==1)
  {
    Serial.println("Go Straight");    
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==1)
  {
    Serial.println("Turn Right");
  }
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==3)
  {
    Serial.println("Turn Left");
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==0)
  {
    Serial.println("Turn Right_Fast");    
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==3)
  {
    Serial.println("Turn Left_Fast");
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==2)
  {
    Serial.println("Turn Right_Fast!!!");
  }
  if(linefollower_2.readSensors()==1 && linefollower_3.readSensors()==3)
  {
    Serial.println("Turn Left_Fast!!!");
  } 
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==0)
  {
    Serial.println("Right");
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==1)
  {
    Serial.println("Left");
  }
 
}





