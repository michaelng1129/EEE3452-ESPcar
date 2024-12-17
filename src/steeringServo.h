#include <Arduino.h>
#include "pin.h"
#include <ESP32Servo.h>

Servo servo;

int pos = 0;

void setupSteeringServo()
{
    servo.attach(SERVO_PIN);
    servo.write(90);
}

void ServoTest()
{
    for (pos = 90; pos <= 135; pos += 1)
    {
        servo.write(pos);
        delay(15);
    }
    for (pos = 135; pos >= 45; pos -= 1)
    {
        servo.write(pos);
        delay(15);
    }
    for (pos = 45; pos <= 90; pos += 1)
    {
        servo.write(pos);
        delay(15);
    }
}

void turnLeft()
{
    for (pos = 90; pos >= 45; pos -= 1)
    {
        servo.write(pos);
        delay(15);
    }
    //delay(5000);
    // for (pos = 45; pos <= 90; pos += 1)
    // {
    //     servo.write(pos);
    //     delay(15);
    // }
}
void turnRight()
{
    for (pos = 90; pos <= 135; pos += 1)
    {
        servo.write(pos);
        delay(15);
    }
    //delay(5000);
    // for (pos = 45; pos <= 90; pos += 1)
    // {
    //     servo.write(pos);
    //     delay(15);
    // }
}
void servoStop()
{
    servo.write(90);
}