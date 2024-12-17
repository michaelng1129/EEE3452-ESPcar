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
    tft.setCursor(0, 0, 2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.println("Hello World!");
}
