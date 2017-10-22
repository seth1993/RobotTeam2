import pygame
import time

#constants
MAX_VAL = 255
AXIS_LEFT_INDEX = 1
AXIS_RIGHT_INDEX = 5


pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0);
joystick.init()


while true:
	pygame.event.get()
	axis_left = int(joystick.get_axis(AXIS_LEFT_INDEX) * MAX_VAL)
	axis_right = int(joystick.get_axis(AXIS_RIGHT_INDEX) * MAX_VAL)
	print(axis_left, axis_right)
	time.sleep(0.5)