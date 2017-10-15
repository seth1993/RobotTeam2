#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define MAX_POWER 255
#define MIN_POWER 0

#define FORWARD 1
#define STOP 0
#define BACKWARD -1

class Motor
{
  private:
    int direction_pin;
    int speed_pin;
    int brake_pin;

    //1 = forward, 0 = stop -1 = backward
    int direction;

    void setup_motor();
    void set_direction_forward();
    void set_direction_backward();
    
  public:
    Motor(int direction_pin, int speed_pin, int brake_pin);
    void drive_forward(int power);
    void drive_backward(int power);
    void drive_stop();
};

#endif
