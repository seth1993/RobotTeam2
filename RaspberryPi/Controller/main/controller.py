import pygame
import time
import RPi.GPIO as GPIO

#constants
MAX_VAL = 255
AXIS_LEFT_INDEX = 1
AXIS_RIGHT_INDEX = 5

#debug LEDs
LED_ON = 18

bluetoothSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600 )

def setup():
	#setup pygame
	pygame.init()
	pygame.joystick.init()

	#setup joystick
	joystick = pygame.joystick.Joystick(0);
	joystick.init()

	#setup LED
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	GPIO.setup(LED_ON,GPIO.OUT)


#formats the number to send by shifting bits
#000000000000 XX XXXXXXXX XX XXXXXXXX
#first 12 bits not used
#next 2 define direction for the left motor    
#next 8 define the speed for the left motor
#next 2 define direction for the right motor
#next 8 define the speed for the right motor
def format_input(left_val, right_val):
	left_num = 1
	if(left_val < 0):
		left_num = 2
		left_val = left_val * -1

	right_num = 1
	if(right_val < 0):
		right_val = 2
		right_val = right_val * -1

	result = 0
	result = result | (left_num << 18)
	result = result | (left_val << 10)
	result = result | (right_num << 8)
	result = result | (right_val)

	return result


def send_input(val):
	bluetoothSerial.write(str(val))



def process_controller_input():
	while true:
	pygame.event.get()
	axis_left = int(joystick.get_axis(AXIS_LEFT_INDEX) * MAX_VAL)
	axis_right = int(joystick.get_axis(AXIS_RIGHT_INDEX) * MAX_VAL)
	formatted_input = format_input(axis_left, axis_right)
	send_input(format_input)


def main():
	setup()

	#turn LED on to show program started
	GPIO.output(LED_ON,GPIO.HIGH)

	process_controller_input()


main()




