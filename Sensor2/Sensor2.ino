#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>


double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeLineFollower linefollower_2(2);
MeLineFollower linefollower_3(3);

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

void move(int power, int _speed)
{
    int leftSpeed = 0;
    int rightSpeed = 0;
    if (power > _speed)
    {
      power = _speed;
    }
    if (power < -_speed)
    {
      power = -_speed;
    }
    if (power > 0)  //左轉
    {
      leftSpeed=_speed;
      rightSpeed=_speed-power;
    }
    
    if (power < 0)  //右轉
    { 
      leftSpeed=_speed+power;
      rightSpeed=_speed;
    } 
    
    if (power == 0)
    { 
      leftSpeed=_speed;
      rightSpeed=_speed;
    } 
    
    motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
    motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}

void setup(){
    Serial.begin(9600);
    
}

int interror = 0;
int olderror = 0;
double Kp=10,Ki=0,Kd=1;
int leftSpeed = 0;
int rightSpeed = 0;
void loop(){
    int r=0,r_f=0,l=0,l_f=0,error=0;
    double lasterror,power;

    if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==1)
  {
    //Serial.println("Go Straight");    
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==1)
  {
    //Serial.println("Turn Right");
    r=1;
  }
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left");
    r_f=-1;
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==0)
  {
    //Serial.println("Turn Right_Fast");    
    l=10;
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left_Fast");
    l_f=-10;
  }
    
    
    error=r+r_f+l+l_f;
    interror += error;
    lasterror = error - olderror;
    olderror = error;
    power = error * Kp + interror * Ki + lasterror * Kd;


    if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==3)
    {
      if(power > 0)
      {
        leftSpeed=0;
        rightSpeed=255;
      }
      if(power < 0)
      {
        leftSpeed=255;
        rightSpeed=0;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
    }
    
    else
    {
      move(power,150);
    }
   
    
    Serial.println(power);
    //delay(500);
}
