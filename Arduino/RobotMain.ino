/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SoftwareSerial.h>


SoftwareSerial BTSerial(0,1); // RX | TX

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

// Set to current motor direction
int ldir = 1;
int rdir = 1;

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps
    Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  
    AFMS.begin();  // create with the default frequency 1.6KHz
    //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
    Serial.begin(9600);
    Serial.println("Sketch HC-0x_FC-114_01_9600");
    Serial.println("Arduino with HC-0x FC-114 is ready");
    Serial.println("Make sure Both NL & CR are set");
    
    // FC-114 default baud rate is 9600
    BTSerial.begin(9600);
    Serial.println("");  
    Serial.println("BTserial started at 115200");

    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void loop() {
  if (BTSerial.available()) {
     String i = BTSerial.readString();
     String lDirection = getValue(i, ' ', 0);
     String lPower = getValue(i, ' ', 1);
     String rDirection = getValue(i, ' ', 2);
     String rPower = getValue(i, ' ', 3);
     Serial.println(lDirection);
     Serial.println(lPower);
     Serial.println(rDirection);
     Serial.println(rPower);
     Serial.println("");
      
     if(lDirection || rDirection) {
      setMotor(1,lDirection.toInt(),lPower.toInt());
      setMotor(0,rDirection.toInt(),rPower.toInt());
     }
  }
  
}

void setMotor(int side, int direction, int speed) {
  if(side && direction == ldir) {
    leftMotor->setSpeed(speed);
  } else if (!side && direction == rdir) {
    rightMotor->setSpeed(speed);
  } else if (side) {
    leftMotor->run(direction);
    leftMotor->setSpeed(speed);
    ldir = direction;
  } else {
    rightMotor->run(direction);
    rightMotor->setSpeed(speed);
    rdir = direction;
  }
}


String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
