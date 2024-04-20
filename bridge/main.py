#!/usr/bin/env python

import time

import paho.mqtt.client as mqtt
import serial

def on_connect(client, userdata, flags, reason_code, properties):
    client.subscribe("/#")

def make_on_message(ser):
    return lambda client, userdata, msg: ser.write(f"{msg.topic}: {msg.payload}\n".encode("utf-8"))

if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyACM0")
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    mqttc.on_connect = on_connect
    mqttc.on_message = make_on_message(ser)

    mqttc.connect("host.docker.internal", 1883, 60)
    mqttc.loop_forever()
