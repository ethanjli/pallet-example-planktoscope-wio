#!/usr/bin/env python

print("starting!")

import time

import paho.mqtt.client as mqtt
import serial

def on_connect(client, userdata, flags, reason_code, properties):
    print("connected!")
    client.subscribe("#")

def make_on_message(ser):
    def on_message(client, userdata, msg):
        print(f"{msg.topic}: {msg.payload}")
        ser.write(f"{msg.topic}: {msg.payload}\n".encode("utf-8"))
    return on_message

if __name__ == "__main__":
    print("connecting to /dev/ttyACM0...")
    ser = serial.Serial("/dev/ttyACM0")
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    mqttc.on_connect = on_connect
    mqttc.on_message = make_on_message(ser)

    print("connecting to mqtt...")
    mqttc.connect("host.docker.internal", 1883, 60)
    mqttc.loop_forever()
