#!/usr/bin/python3
import RPi.GPIO as GPIO
import time
import serial
import threading
ser = serial.Serial('/dev/ttyACM0', 9600)

start = 0b10000000;
A = 0b01000000;
B = 0b00100000;
C = 0b00010000;
D = 0b00001000;
E = 0b00000100;
F = 0b00000010;
G = 0b00000001;

while True:
    #bytearr = int.from_bytes(ser.read(size=4), byteorder='little')
    bytearr = ser.read(size=4)
    print('\n')
    idx = 0;
    while True:
        if bytearr[idx] & start:
            # do something with other three
            idx = (idx + 1) % 4
            print(bytearr[idx])
            idx = (idx + 1) % 4
            print(bytearr[idx])
            idx = (idx + 1) % 4
            print(bytearr[idx])
            break
        else:
            idx = (idx + 1) % 4
        
    #for k in bytearr:
        
        #print(k)


#    if(ser.read(size=1) == start):
#        print("Start")
#        byte0 = ser.read(size=1)
#        if(A & byte0):
#             print("A")
#        if(B & byte0):
#             print("B")
#        if(C & byte0):
#            print("C")
#        if(D & byte0):
#            print("D")
#        if(E & byte1):
#            print("E")
#        if(F & byte1):
#            print("F")
#        if(G & byte1):
#            print("G")
#
#        byte1 = ser.read(size=1)
#        print(byte1)
#
#        byte2 = ser.read(size=1)
#        print(byte2)
