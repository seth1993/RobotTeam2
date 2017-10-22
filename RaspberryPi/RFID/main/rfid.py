import RPi.GPIO as GPIO
import MFRC522
from Adafruit_IO import Client
import thread
import time

#constants
ADAFRUIT_IO_KEY = 'd1a1bd3737714fa488e0364c775a4b4d'
LED_SCANNED = 0
LED_UPLOAD = 0
LED_ERROR = 0
DELAY = 0.5

aio = Client(ADAFRUIT_IO_KEY)


def setup():
	#setup LED
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	GPIO.setup(LED_SCANNED,GPIO.OUT)
	GPIO.setup(LED_UPLOAD,GPIO.OUT)
	GPIO.setup(LED_ERROR,GPIO.OUT)


def turn_led_on(led):
	GPIO.output(led,GPIO.HIGH)


def turn_led_off(led):
	GPIO.output(led,GPIO.LOW)


def upload_to_adafruit(message):
	aio.send('Team 2', message)


def check_for_card():

	 # Scan for cards    
    (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)

    # If we have the UID, continue
    if status == MIFAREReader.MI_OK:

    	#set the led to indicate a card was scanned
    	turn_led_on(LED_SCANNED)

    	# Get the UID of the card
    	(status,uid) = MIFAREReader.MFRC522_Anticoll()

        # Print UID
        # print "Card read UID: "+str(uid[0])+","+str(uid[1])+","+str(uid[2])+","+str(uid[3])
        uid_string = str(uid[0])+","+str(uid[1])+","+str(uid[2])+","+str(uid[3])

        turn_led_on(LED_UPLOAD)

        #start a new thread to handle upload
        try:
        	thread.start_new_thread(upload_to_adafruit, (uid_string,))
        except:
        	#turn on error led
        	turn_led_on(LED_ERROR)

        time.sleep(DELAY)

        #turn off all LEDs
        turn_led_off(LED_SCANNED)
        turn_led_off(LED_UPLOAD)
        turn_led_off(LED_ERROR)


def main():
	setup()
	check_for_card()



    



