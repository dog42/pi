import RPi.GPIO as GPIO
import time

pin = 14
GPIO.setmode(GPIO.BCM) #Pinbelegung nach Broadcom SOC channel
GPIO.setup(pin, GPIO.OUT)
servo = GPIO.PWM( pin, 50) # an GPIO 14 PWM mit 50Hz (20ms) 
servo.start(7) # Start-Position/-Pulslange(1ms)
try:
  while True:
    servo.ChangeDutyCycle(2.5)
    time.sleep(1)
    servo.ChangeDutyCycle(7)
    time.sleep(1)
    servo.ChangeDutyCycle(11.5)
    time.sleep(1)
    servo.ChangeDutyCycle(7)
    time.sleep(4)
except KeyboardInterrupt:
  servo.stop()
  GPIO.cleanup()
