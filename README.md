# rgbUrself-Hat

This is project is scaleable so you can edit the amount of pixels available to your strip easily in the sketch globals. Think about your own power solution with regards to the amount of pixels in your strip. You can easily run a lot of them on USB power and run them directly from the NodeMCU Vin  pin but will very quickly run into issues with a lot of pixels at max brightness and full white (drawing most current). There is some control over the voltage and mah's via code which I have put in, assuming you're using a usb port by default (5v/500mah)..

## What  can the lightstrip/hat do via chat?

You can lengthen or shorten the delay between its default routines with !hat faster or !hat slower (changes by 1 second increments from baseline 10 seconds delay)

You can also skip directly to the next routine with !hat next

## How can chat do this?

Add a streamlabs (or other) chat command for !hat then have its output say  "{user.name} changed delay: {1}"

Then chat can do !hat faster/slower/next

## Why the yeelight smartbulb integration? 

For bits, cheers, subs, follows, hosts, gifts and tips my main lightbulb will run a lightshow routine independant of the hat, right now the hat is not connected to these events but will be included in a future update. 

You can also change your smartbulbs with !default (max brightness/lumens) !day (100W tungston emulated bulb) !warm (40W tungston emulated bulb) !nm (night mode, very dim light)

The two bots work independent of each other so if you only have rgb strips use RGBHat and if you only have a yeelight smartbulb just use the python bot, both can connect to IRC separately using the same bot account, just grab the OAuth code from twitch and fill out the relevant section of both bots. If you only run one bot you will lose some automatic chat output I have set up between the two within certain events.

I'm using streamlabs as my chat-bot and backend command manager but you can use any other bot (moobot/nightbot etc). Unless you're a very very patient person who can handle someone taking advantage I'd recommend not doing the following but you *could* edit the bot to allow anyone to freely use all your commands. 

# Pre-requisites

Your streamlabs cloudbot needs to be in your channel, given moderator and have chat alerts enabled (under Modules in the cloudbot sub menu).

You need the Yeelight library for the Python bot `pip/pip3 install yeelight` and the IP address of the bulb on your network (check router or run `nmap -sn 192.168.whatever.* > nmapresult.txt` and check the txt file) Changing whatever to a real number, mine is 1.

You also need the IRCClient library https://github.com/fredimachado/ArduinoIRC/tree/master/src imported into your arduino IDE

And last but not least, using your streamlabs or moobot bot, you need a !hat command that outputs {user.name} flooped the hat to: {1} 
PS. {1} = the colour, it will literally output anything the person says right now, example !hat bacon. The bot will output that you flooped the hat to: bacon and the strip will ignore your input. I plan to default run a purple routine for this eventually to prevent people wasting loyalty points.



# Running

Start the cr0light(Python bot) using `python3 main.py` (or add a @reboot crontab so you don't have manually initialise after a reboot)

The RGBHat.ino script will begin directly after uploading and print "Ready to go Boss!" in your channel if everything went smoothly.

# Why it doesn't work for me

No idea. Did you install python3 and yeelight correctly?

# Donate

If my work improves your stream or you saved time coding, you can buy me a coffee =]

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=N2VPZXYRRXGN6)




