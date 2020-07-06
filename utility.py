import config
import socket
import time
from yeelight import *
from yeelight.transitions import *
bulb = Bulb("192.168.1.87", port=55443, auto_on=True)

def chat(sock, msg):
    """
    Send a chat message to the server.
    Keyword arguments:
    sock -- the socket over which to send the message
    msg  -- the message to be sent
    """
    sock.send(("PRIVMSG {} :{}\r\n".format(config.CHAN, msg)).encode("UTF-8"))


def timeout(sock, user, secs=600):
    """
    Time out a user for a set period of time.
    Keyword arguments:
    sock -- the socket over which to send the timeout command
    user -- the user to be timed out
    secs -- the length of the timeout in seconds (default 600)
    """
    chat(sock, ".timeout {}".format(user, secs))

def flicker():
    follows = Flow(
    count=6,
    transitions=pulse(0, 255, 0, duration=500, brightness=100),
)
    attempts = 30
    for j in range(attempts):
            try:
                bulb.start_flow(follows)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 2 seconds. Retry attempt:",j+1)
                    time.sleep(2)
                    continue
                else:
                    print(str(s))
            break
def tipped():
    tipped = Flow(
    count=6,
    transitions=pulse(0, 0, 255, duration=500, brightness=100),
)
    attempts = 30
    for j in range(attempts):
            try:
                bulb.start_flow(tipped)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 2 seconds. Retry attempt:",j+1)
                    time.sleep(2)
                    continue
                else:
                    print(str(s))
            break
        
def sub():
    subs = Flow(
    count=2,
    transitions=police2(duration=500,brightness=100),
)
    attempts = 30
    for j in range(attempts):
            try:
                bulb.start_flow(subs)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 2 seconds. Retry attempt",j+1)
                    time.sleep(2)
                    continue
                else:
                    print(str(s))
            break
        
def default():
    attempts = 5
    for j in range(attempts):
            try:
                bulb.set_rgb(201,226,255)
                bulb.set_brightness(100)
                bulb.set_color_temp(5000)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 5 seconds. Retry attempt",j+1)
                    time.sleep(5)
                    continue
                else:
                    print(str(s))
            break
def day():
    attempts = 5
    for j in range(attempts):
            try:
                bulb.set_rgb(255,214,170)
                bulb.set_brightness(100)
                bulb.set_color_temp(2850)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 5 seconds. Retry attempt",j+1) #j+1 for human readability
                    time.sleep(5)
                    continue
                else:
                    print(str(s))
            break
def night():
    attempts = 5
    for j in range(attempts):
            try:
                bulb.set_rgb(255,147,41)
                bulb.set_brightness(5)
                bulb.set_color_temp(1900)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 5 seconds. Retry attempt",j+1)
                    time.sleep(5)
                    continue
                else:
                    print(str(s))
            break  
def warm():
    attempts = 5
    for j in range(attempts):
            try:
                bulb.set_rgb(255,197,143)
                bulb.set_brightness(70)
                bulb.set_color_temp(2300)
            except Exception as s:
                if j < attempts -1:
                    print("Trying again in 5 seconds. Retry attempt",j+1)
                    time.sleep(5)
                    continue
                else:
                    print(str(s))
            break
