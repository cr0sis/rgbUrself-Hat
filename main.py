#!/usr/bin/env python
import config
import utility
import socket
import time
import re
from yeelight import *
from yeelight.transitions import *
bulb = Bulb("192.168.1.87", port=55443, auto_on=True)

CHAT_MSG = re.compile(r"^:\w+!\w+@\w+\.tmi\.twitch\.tv PRIVMSG #\w+ :")

try:
    s = socket.socket()
    s.connect((config.HOST, config.PORT))
    s.send("PASS {}\r\n".format(config.PASS).encode("utf-8"))
    s.send("NICK {}\r\n".format(config.NICK).encode("utf-8"))
    s.send("JOIN {}\r\n".format(config.CHAN).encode("utf-8"))
    connected = True #Socket succefully connected
except Exception as e:
    print(str(e))
    connected = False #Socket failed to connect

def bot_loop():
    bulb.stop_music()
    print("Music mode off.")
    bulb.start_music(0)
    print("Music mode on.")
    while connected:
        response = s.recv(1024).decode("utf-8")
        if response == "PING :tmi.twitch.tv\r\n":
            s.send("PONG :tmi.twitch.tv\r\n".encode("utf-8"))
            print("Pong")
        else:
            username = re.search(r"\w+", response).group(0) 
            message = CHAT_MSG.sub("", response)
            print(username + ": " + response)
            for pattern in config.COMMANDS:
                if re.search(pattern[0], message) and (username == "streamlabs" or username == "cr0sis"):
                    utility.chat(s, pattern[1])
                    if (pattern[0] == '!default'):
                        utility.default()
                    if (pattern[0] == 'subscribed'):
                        utility.sub()
                    if (pattern[0] == 'following'):
                        utility.flicker() 
                    if (pattern[0] == '!day'):
                        utility.day()
                    if (pattern[0] == '!nm'):
                        utility.night()
                    if (pattern[0] == '!warm'):
                        utility.warm()
                    if (pattern[0] == 'tipped'):
                        utility.tipped()
                    if (pattern[0] == 'cheered'):
                        utility.flicker()
                    if (pattern[0] == 'raided'):
                        utility.sub()
                    if (pattern[0] == 'gifted'):
                        utility.tipped()
                    if (pattern[0] == 'hosted'):
                        utility.sub()
                    break
        time.sleep(1 / config.RATE)
if __name__ == "__main__":
    bot_loop()

    
