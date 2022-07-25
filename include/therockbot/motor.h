#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct sMotor
{
    unsigned int in1;
    unsigned int in2;
    unsigned int pwm;

    void init()
    {
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(pwm, OUTPUT);
    }

    void setSpeed(const int speed)
    {
        if (speed == 0)
        {
            analogWrite(pwm, 0);
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }
        else
        {
            if (speed > 0)
            {
                digitalWrite(in1, HIGH);
                digitalWrite(in2, LOW);
            }
            else
            {
                digitalWrite(in1, LOW);
                digitalWrite(in2, HIGH);
            }
            analogWrite(pwm, std::min(255, abs(speed)));
        }
    }

    void stop()
    {
        setSpeed(0);
    }
};

#endif /* MOTOR_H */
