# rgbUrself-Hat

Why hat? I wear a hat on stream with a pixel strip integrated into it that viewers can spend loyalty points to change its colour for short period of time, the Hat refers to this. This is scaleable so you can edit the amount of pixels available to your strip easily in the sketch globals. Think about your own power solution with regards to the amount of pixels in your strip. You can easily run a lot of them on USB power and run them directly from the NodeMCU Vin (acts as Vout when board is powered by usb **Boards are different, check yours**) pin but will very quickly run into issues with a lot of pixels at max brightness and full white (drawing most current).

What does the RGB strip lightshow look like? Think knightrider, only way more flamboyant. 

Tune into my stream to see it in action, schedule @ https://cr0s.is/schedule.php I am happy to field questions about this while live too. Short demo stream (no voice so it's a bit weird) https://www.twitch.tv/videos/671704549?t=0h2m23s note to self: replace with youtube link when twitch vod deleted

Why the yeelight smartbulb integration? For bits, cheers, subs, follows, hosts, gifts and tips my main lightbulb will run a lightshow routine independant of the hat, right now the hat is not connected to these events but will be included in a future update.

The two bots work independent of each other so if you only have rgb strips use RGBHat and if you only have a yeelight smartbulb just use the python bot, both can connect to IRC separately using the same bot account, just grab the OAuth code from twitch and fill out the relevant section of both bots. If you only run one both you will lose some automatic chat output I have set up between the two between certain routines.

I'm using streamlabs as my chat-bot and backend command manager but you can use any other bot (moobot/nightbot etc). Unless you're a very very patient person who can handle someone taking advantage I'd recommend not doing the following but you *could* edit the bot to allow anyone to freely use all your commands. 

# Pre-requisites

You need the Yeelight library for the Python bot (pip/pip3 install yeelight) and the IP address of the bulb on your network (check router or run nmap -sn 192.168.whatever.* > nmapresult.txt and check the txt file) Changing whatever to a real number, mine is 1.

You also need the IRCClient library https://github.com/fredimachado/ArduinoIRC imported into your arduino IDE


# Running

Start the cr0light(Python bot) using python3 main.py (or add a @reboot crontab so you don't have manually initialise after a reboot)

The RGBHat.ino script will begin directly after uploading and print "Ready to go Boss!" in your channel if everything went smoothly.

# Why it doesn't work for me

No idea

# Donate

If my work improves your stream or you saved time coding, you can buy me a coffee =]

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=N2VPZXYRRXGN6)




