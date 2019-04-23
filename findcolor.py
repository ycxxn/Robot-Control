#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 12 16:17:19 2018

@author: pccurobot
"""
import cv2
import numpy as np
import time
from picamera.array import PiRGBArray
from picamera import PiCamera


def nothing(x):
    pass

kernel = np.ones((8, 8), np.uint8)  
camera = PiCamera()
camera.resolution = (640,480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

cv2.namedWindow('mask')

# create trackbars for color change
cv2.createTrackbar('LH','mask',156,255,nothing)
cv2.createTrackbar('LS','mask',43,255,nothing)
cv2.createTrackbar('LV','mask',46,255,nothing)
cv2.createTrackbar('HH','mask',180,255,nothing)
cv2.createTrackbar('HS','mask',255,255,nothing)
cv2.createTrackbar('HV','mask',255,255,nothing)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
 
    # Convert BGR to HSV
    cap = frame.array
    hsv = cv2.cvtColor(cap, cv2.COLOR_BGR2HSV)
    
    lr = cv2.getTrackbarPos('LH','mask')
    lg = cv2.getTrackbarPos('LS','mask')
    lb = cv2.getTrackbarPos('LV','mask')
    hr = cv2.getTrackbarPos('HH','mask')
    hg = cv2.getTrackbarPos('HS','mask')
    hb = cv2.getTrackbarPos('HV','mask')
    
    print (lr,lg,lb,hr,hg,hb)

    # define range of blue color in HSV
    lower_blue = np.array([lr,lg,lb])
    upper_blue = np.array([hr,hg,hb])

    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    mask = cv2.erode(mask,kernel,iterations=2)
    mask = cv2.dilate(mask,kernel,iterations=2)

    rawCapture.truncate(0)
    cv2.imshow('frame',cap)
    cv2.imshow('mask',mask)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

           
for i in range(1,10):
    cap.release()
    cv2.destroyAllWindows()
