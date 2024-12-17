#include <Arduino.h>
#include "pin.h"

#define LEDC_CHANNEL1 1
#define LEDC_CHANNEL2 1
#define LEDC_CHANNEL3 2

#define LEDC_FREQUENCY 5000
#define LEDC_RESOLUTION 8

void setupLED()
{
    pinMode(LEDR_PIN, OUTPUT);
    pinMode(LEDG_PIN, OUTPUT);
    pinMode(LEDB_PIN, OUTPUT);

    ledcSetup(LEDC_CHANNEL1, LEDC_FREQUENCY, LEDC_RESOLUTION);
    ledcAttachPin(LEDR_PIN, LEDC_CHANNEL1);

    ledcSetup(LEDC_CHANNEL2, LEDC_FREQUENCY, LEDC_RESOLUTION);
    ledcAttachPin(LEDG_PIN, LEDC_CHANNEL2);

    ledcSetup(LEDC_CHANNEL3, LEDC_FREQUENCY, LEDC_RESOLUTION);
    ledcAttachPin(LEDB_PIN, LEDC_CHANNEL3);
}

void setLEDBrightness(int channel, int brightness)
{
    ledcWrite(channel, brightness);
}

void runChaseEffect()
{
    for (int i = 0; i < 3; i++)
    {
        setLEDBrightness(LEDC_CHANNEL1, (i == 0) ? 255 : 0);
        delay(1000);
        setLEDBrightness(LEDC_CHANNEL2, (i == 1) ? 255 : 0);
        delay(1000);
        setLEDBrightness(LEDC_CHANNEL3, (i == 2) ? 255 : 0);
        delay(1000);
    }
}

void fadeEffect(int channel)
{

    for (int brightness = 0; brightness <= 255; brightness++)
    {
        setLEDBrightness(channel, brightness);
        delay(10);
    }

    for (int brightness = 255; brightness >= 0; brightness--)
    {
        setLEDBrightness(channel, brightness);
        delay(10);
    }
}