#include "Motor.h"

Motor *right = new Motor(12, 3 ,9);
Motor *left = new Motor(13, 11, 8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  right->drive_forward(100);
  left->drive_forward(100);
  delay(4000);

}
