import serial
import time

#ser = serial.Serial("/dev/ttyAMA0" , baudrate = 57600 , timeout = 1.0)
ser = serial.Serial("COM5" , baudrate = 57600 , timeout = 1.0)

def R1(data):  
    senddata = bytearray()
    senddata.append(0xff)
    senddata.append(0x55)
    senddata.append(data)
    return senddata

while(1) :
    TXD = R1(1)
    ser.write(TXD)
    print(TXD)
    time.sleep(1)
    TXD = R1(2)
    ser.write(TXD)
    time.sleep(1)
