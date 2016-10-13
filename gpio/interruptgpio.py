import RPi.GPIO as GPIO
import time

Counter = 0
GPIO.setmode(GPIO.BCM)#Pinbelegung nach Broadcom SOC channel

GPIO.setup(24, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)  

# ISR
def Interrupt(channel):  
	global Counter
	Counter = Counter + 1
	print "Counter " + str(Counter) 
	
# Interrupt Event hinzufuegen. Pin 24, auf steigende Flanke reagieren und ISR "Interrupt" deklarieren
GPIO.add_event_detect(24, GPIO.RISING, callback = Interrupt, bouncetime = 200)   
while True:
	time.sleep(1)