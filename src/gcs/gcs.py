#!/usr/bin/python3

import keyboard
import serial
import time

def to_serializable(cmd):
    cmd = max(-254, min(254, cmd))
    return int(cmd/2 + 127) & 0xFF

if __name__ == "__main__":
    radio = serial.Serial("/dev/ttyUSB0", baudrate=57600)
    to_write = []
    while True:
        to_write.append(0xDE)
        if keyboard.is_pressed('z'):
            to_write.append(to_serializable(255))
        elif keyboard.is_pressed('s'):
            to_write.append(to_serializable(-254))
        else:
            to_write.append(to_serializable(0))
        if keyboard.is_pressed('q'):
            to_write.append(to_serializable(255))
        elif keyboard.is_pressed('d'):
            to_write.append(to_serializable(-254))
        else:
            to_write.append(to_serializable(0))
        print(bytearray(to_write))
        radio.write(bytearray(to_write))
        to_write.clear()
        time.sleep(0.1)