import cv2 as cv
import numpy as np
import time
from picamera.array import PiRGBArray
from picamera import PiCamera
import serial
import time

mask=None
capture=None

ser = serial.Serial("/dev/ttyAMA0" , baudrate = 57600 , timeout = 1.0)
kernel = np.ones((10, 10), np.uint8) 

camera = PiCamera()
camera.resolution = (640,480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))
time.sleep(0.1)
kernel = np.ones((8, 8), np.uint8)  

Blue_lower = np.array([100,43,46])
Blue_upper = np.array([124,255,255])
Red_lower1 = np.array([0,43,46])
Red_upper1 = np.array([10,255,255])
Red_lower2 = np.array([156,43,46])
Red_upper2 = np.array([180,255,255])
Green_lower = np.array([35,43,46])
Green_upper = np.array([77,255,255])
Orange_lower = np.array([0,43,46])
Orange_upper = np.array([30,255,255])

cv.namedWindow("camera",1)
cv.namedWindow("camera2",1)
a=0

def R1(data):  
    senddata = bytearray()
    senddata.append(0xff)
    senddata.append(0x55)
    senddata.append(data)
    return senddata

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    cap = frame.array

    hsv = cv.cvtColor(cap,cv.COLOR_BGR2HSV)
    hsv = cv.erode(hsv,kernel,iterations=2)
    hsv = cv.dilate(hsv,kernel,iterations=2)
    
    Blue_mask = cv.inRange(hsv, Blue_lower, Blue_upper)
##    Red1_mask = cv.inRange(hsv, Red_lower1, Red_upper1)
##    Red2_mask = cv.inRange(hsv, Red_lower2, Red_upper2)
##    Green_mask = cv.inRange(hsv, Green_lower, Green_upper)
    
    c1 = cv.countNonZero(Blue_mask)
##    c2 = cv.countNonZero(Red1_mask+Red2_mask)
##    c3 = cv.countNonZero(Green_mask)

    Blue_mask = cv.erode(Blue_mask,kernel,iterations=2)
    Blue_mask = cv.dilate(Blue_mask,kernel,iterations=2)
        
    if(c1>95000):
       a = 2
       TXD = R1(2)
       ser.write(TXD)
    elif(c1<30000):
       a = 1
       TXD = R1(1)
       ser.write(TXD)
    
    print(a)
    print("c1:  " +str(c1))
##  print("c2:  " +str(c2))
##  print("c3:  " +str(c3))
    cv.imshow("camera2",Blue_mask)
    cv.imshow("camera" ,cap)

    if cv.waitKey(10) == 27:
        
        time.sleep(0.5)
        break

    rawCapture.truncate(0)
for i in range(1,10):
    ser.close()
    cv.destroyAllWindows()
    cv.waitKey(1)
