import time as tm
import datetime
import pygame

sound_file = "HomecomingSamsungRingtone.mp3"
def input_alarm():
    print("set alarm:")
    run = 1
    while run == 1:
        try:
            hours = int(input("hours: "))
            if hours < 0 or hours >23:
                print("must be between 0 to 24")
                input_alarm()
                break
            minutes = int(input("minutes: "))
            if minutes < 0 or minutes >59:
                print("must be between 0 to 60")
                input_alarm()
                break
            seconds = int(input("seconds: "))
            if seconds < 0 or seconds >59:
                print("must be between 0 to 60")
                input_alarm()
                break
            run = 0
        except:
            print("invalid input")
            input_alarm()
            break
    if hours < 10:
        hours = "0"+str(hours)
    else:
        hours = str(hours)
    if minutes < 10:
        minutes = "0"+str(minutes)
    else:
        minutes = str(minutes)
    if seconds < 10:
        seconds = "0"+str(seconds)
    else:
        minutes = str(minutes)
    
    usersetalarm = f"{hours}:{minutes}:{seconds}"
    return usersetalarm

def alarm(alarm_clock):
    run = 1
    while run == 1:
        current_time = time_now()
        print(current_time)
        tm.sleep(1)
        if current_time == alarm_clock:
            print("WAKE UP")
            pygame.mixer.init()
            pygame.mixer.music.load(sound_file)
            pygame.mixer.music.play()
            tm.sleep(15)
            run = 0


def time_now():
    now = datetime.datetime.now()
    now = now.strftime("%H:%M:%S")
    return now

if __name__ == '__main__':
    alarm1 = input_alarm()
    alarm(alarm1)
    print(time_now())
    print("WAKE UP NIGGA")
