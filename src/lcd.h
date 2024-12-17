#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setupLCD()
{
    tft.init();
    tft.setRotation(1);
    // tft.invertDisplay(0);
}

void drawScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.println("192.168.68.141");
}


void drawScreen1(const char* word)
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.println(word);
}
void drawScreen2(float value)
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(50, 0);
    char buffer[20];
    dtostrf(value, 4, 2,buffer);
    tft.println("Temperature: ");
    tft.println(buffer);
    delay(2000);
}

void drawScreen3(float value)
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(50, 50);
    char buffer[20];
    dtostrf(value, 4, 2,buffer);
    tft.println("Humidity: ");
    tft.println(buffer);
    delay(2000);
}