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
    if (power > 2*_speed)
    {
      power = 2*_speed;
    }
    if (power < 2*-_speed)
    {
      power = 2*-_speed;
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
    Serial.println(power);
}

void setup(){
    Serial.begin(9600);
    
}

int interror = 0;
int olderror = 0;
double Kp=200,Ki=0,Kd=0;
int leftSpeed = 0;
int rightSpeed = 0;
void loop(){
    int r=0,rr=0,rrr=0,l=0,ll=0,lll=0,error=0;
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
    l=-1;
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==0)
  {
    //Serial.println("Turn Right_Fast");
    rr=5;  
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left_Fast");
    ll=-5;
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==2)
  {
    //Serial.println("Turn Right_Fast!!!");
    rrr=10;
  }
  if(linefollower_2.readSensors()==1 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left_Fast!!!");
    lll=-10;
  }
    
    
    error=r+rr+rrr+l+ll+lll;
    interror += error;
    lasterror = error - olderror;
    olderror = error;
    power = error * Kp + interror * Ki + lasterror * Kd;


    //if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==3)
    {
      motor_9.run((9)==M1?-(-120):(-120));
      motor_10.run((10)==M1?-(-120):(-120));
    }
    //else
    {
      move(power,200);
    }
    
   
    
    //Serial.println(power);
    //delay(500);
}
