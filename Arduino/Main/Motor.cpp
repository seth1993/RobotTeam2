#include "Motor.h"

Motor::Motor(int direction_pin, int speed_pin, int brake_pin)
{
  this->direction_pin = direction_pin;
  this->speed_pin = speed_pin;
  this->brake_pin = brake_pin;

  setup_motor();
}

void Motor::setup_motor()
{
  pinMode(direction_pin, OUTPUT);
  pinMode(brake_pin, OUTPUT);
}

void Motor::drive_forward(int power)
{
  Serial.print("going  foward");
  if(direction != FORWARD)
  {
    set_direction_forward();
  }
  analogWrite(speed_pin, power);
}

void Motor::drive_backward(int power)
{
  Serial.print("going  backward");
  if(direction != BACKWARD)
  {
    set_direction_backward();
  }
  analogWrite(speed_pin, power);
}

void Motor::drive_stop()
{
  digitalWrite(brake_pin, HIGH);
}

void Motor::set_direction_forward()
{
  digitalWrite(direction_pin, HIGH);
  digitalWrite(brake_pin, LOW);
}

void Motor::set_direction_backward()
{
  digitalWrite(direction_pin, LOW);
  digitalWrite(brake_pin, LOW);
}
