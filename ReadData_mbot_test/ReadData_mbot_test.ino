#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>
byte number = 0;
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeRGBLed rgbled_7(7, 7==7?2:4);
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
unsigned char table[8] = {0};

void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      int err = 80;
      if(direction == 1)
      {
          leftSpeed = speed;
          rightSpeed = speed;
      }
      if(direction == 2)
      {
          leftSpeed = -speed;
          rightSpeed = -speed;
      }
      if(direction == 3) 
      {
          leftSpeed = speed;
          rightSpeed = speed-err;
      }
      if(direction == 4) 
      {
          leftSpeed = speed-err;
          rightSpeed = speed;
      }
      if(direction == 5) 
      {
          leftSpeed = -speed+err;
          rightSpeed = -speed;
      }
      if(direction == 6) 
      {
          leftSpeed = -speed;
          rightSpeed = -speed+err;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
 

  void setup()
  {
     Serial.begin(57600);
     //move(1,0); //程式開始mbot直行
  }

  void loop(){
    int readdata = 0, count = 0;
    if (Serial.available()>0)  
    {
      while((readdata = Serial.read()) != (int)-1)
      {
        table[count] = readdata;
        count++;
        delay(5);
      }
      //Procotol: FF 55 data
      if((table[0] == 255) && (table[1] == 85))
      {
        Serial.println(table[2],DEC);
        if(table[2]==0){
          move(2, 0);
        }
        if(table[2]==1){
          move(1, 150);
        }
        if(table[2]==2){
          move(2, 150);
        }
        if(table[2]==3){
          move(3, 150);
        }
        if(table[2]==4){
          move(4, 150);
        }
        if(table[2]==5){
          move(5, 150);
        }
        if(table[2]==6){
          move(6, 150);
        }
        
      } 
    }   
  }
        
        
        
        
        
        
      
