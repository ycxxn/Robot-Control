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
    
  
   
    if (power > 0)
    {
      leftSpeed=_speed;
      rightSpeed=_speed-power;
    }
    //左轉
    if (power < 0)
    { 
      leftSpeed=_speed+power;
      rightSpeed=_speed;
    } 
    //右轉
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
double Kp=20,Ki=0.1,Kd=0;
int leftSpeed = 0;
int rightSpeed = 0;
void loop(){
    int rr=0,rl=0,r_all=0,lr=0,ll=0,l_all=0,error=0;
    double lasterror,power;
    if(linefollower_3.readSensors()==1)
    {
      rr=-1;
    }
   
    if(linefollower_3.readSensors()==0)
    {
      r_all=-5;
    }
    
    if(linefollower_2.readSensors()==2)
    {
      ll=1;
    }
    if(linefollower_2.readSensors()==0)
    {
      l_all=5;
    }
    
    if(linefollower_2.readSensors()==1)
    { 
      lr=-30;
    }
    if(linefollower_3.readSensors()==2)
    {
      rl=30;
    }
    
    
    error=rr+r_all+ll+l_all;
    interror += error;
    lasterror = error - olderror;
    olderror = error;
    power = error * Kp + interror * Ki + lasterror * Kd;


    
    move(power,150);
   
    
    Serial.println(power);
    //delay(500);
}


