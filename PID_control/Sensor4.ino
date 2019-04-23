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

int left,right;

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

    if (power == 0)  //直行
    { 
      leftSpeed=_speed;
      rightSpeed=_speed;
    }
    if (power > 0)  //左轉
    {
      leftSpeed=_speed;
      rightSpeed=_speed-power;
      left=leftSpeed;
      right=rightSpeed;
    }
    if (power < 0)  //右轉
    { 
      leftSpeed=_speed+power;
      rightSpeed=_speed;
      left=leftSpeed;
      right=rightSpeed;
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
double Kp=90,Ki=0.04,Kd=90;
int leftSpeed = 0;
int rightSpeed = 0; 
void loop(){
  int r=0,rr=0,rrr=0,l=0,ll=0,lll=0,r_=0,l_=0,error=0;
  double lasterror,power;
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==1)
  {
    //Serial.println("Go Straight");    
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==1)
  {
    //Serial.println("Turn Right");
    r=0.9;
  }
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left");
    l=-0.9;
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==0)
  {
    //Serial.println("Turn Right_Fast");
    rr=3;  
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left_Fast");
    ll=-3;
  }
  if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==2)
  {
    //Serial.println("Turn Right_Fast!!!");
    rrr=4;
  }
  if(linefollower_2.readSensors()==1 && linefollower_3.readSensors()==3)
  {
    //Serial.println("Turn Left_Fast!!!");
    lll=-4;
  }
  if(linefollower_2.readSensors()==2 && linefollower_3.readSensors()==0)
  {
    //Serial.println("Right");
    r_=1;
  }
  if(linefollower_2.readSensors()==0 && linefollower_3.readSensors()==1)
  {
    //Serial.println("Left");
    l_=-1;
  }
    
    
    error=r+rr+rrr+l+ll+lll+r_+l_;
    interror += error;
    lasterror = error - olderror;
    olderror = error;
    power = error * Kp + interror * Ki + lasterror * Kd;

    if(linefollower_2.readSensors()==3 && linefollower_3.readSensors()==3)
    {
      motor_9.run((9)==M1?-(left):(left));
      motor_10.run((10)==M1?-(right):(right));
      //motor_9.run((9)==M1?-(0.5*interror):(0.5*interror));
      //motor_10.run((10)==M1?-(-0.5*interror):(-0.5*interror));
    }
    else
    {
       move(power,255);
    }
   
    //Serial.println(power);
    //delay(500);
}
