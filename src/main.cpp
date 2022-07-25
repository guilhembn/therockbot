#include <Arduino.h>

#include "therockbot/motor.h"
#include "therockbot/pinout.h"

sMotor motorLeft({MOT1_IN1, MOT1_IN2, MOT1_PWM});
sMotor motorRight({MOT2_IN1, MOT2_IN2, MOT2_PWM});

unsigned long nextMotorControlTime = 0;
unsigned long now = 0;
unsigned int motorControlPeriod = 10;
int cmd_vx = 0;
int cmd_vtheta = 0;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(57600);
  motorLeft.init();
  motorRight.init();
  pinMode(2, OUTPUT);
}

void loop()
{
  now = millis();
  if (Serial2.available() >= 3)
  {
    int start = Serial2.read();
    if (start == 0xDE)
    {
      cmd_vx = (Serial2.read() - 127) * 2;
      cmd_vtheta = (Serial2.read() - 127) * 2;
    }
  }

  if (now >= nextMotorControlTime)
  {
    int motorLeftCmd = (cmd_vx + cmd_vtheta);  // / 2;
    int motorRightCmd = (cmd_vx - cmd_vtheta); // / 2;
    motorLeft.setSpeed(motorLeftCmd);
    motorRight.setSpeed(motorRightCmd);
    nextMotorControlTime = now + motorControlPeriod;
  }
}
