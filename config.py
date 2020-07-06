HOST = "irc.twitch.tv"                        # This is Twitchs IRC server
PORT = 6667                                   # Twitch IRC server listens on port 6767
NICK = "Yourbot"                                    # Twitch username your using for your bot
PASS = "oauth:123456fnsdlfnwslfnslfnslfnslfn" # your Twitch OAuth token
CHAN = "#yourchan"                              # The channel you want the bot to join. :D
RATE = (20/30)                                # messages per seccond
COMMANDS = [
    [r"!discord", "The official discord is: coming soon!"],
    [r"following", "Running lightshow routine."],
    [r"subscribed", "Running lightshow routine."],
    [r"!default", "Flooping lights to full bright."],
    [r"!day", "Flooping lights to day."],
    [r"!warm", "Flooping lights to warm."],
    [r"!nm", "Flooping lights to night mode."],
    [r"tipped", "Running lightshow routine."],
    [r"cheered", "Running lightshow."],
    [r"raided", "Running lightshow."],
    [r"gifted", "Running lightshow ."],
    [r"hosted", "Running lightshow."],
    [r"flooped the hat to:", "Hat colour will be changed for 69 passes ASAP, if it was changed recently you can queue up the next colour before it goes back to rainbow"]

]
