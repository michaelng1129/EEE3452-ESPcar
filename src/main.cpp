#include <Arduino.h>
#include <WiFi.h>

#include "pin.h"
#include "led.h"
#include "motor.h"
#include "lcd.h"
#include "steeringServo.h"
#include "thSensor.h"

const char *ssid = "ENG-LAB-N2";
const char *password = "12345678";

WiFiServer server(80);

String stringstatus = "LED red off";

void setupwifi()
{
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void testall()
{
  setLEDBrightness(LEDC_CHANNEL1, 128);
  delay(1000);
  setLEDBrightness(LEDC_CHANNEL2, 255);
  delay(1000);
  setLEDBrightness(LEDC_CHANNEL3, 128);
  delay(1000);
  setLEDBrightness(LEDC_CHANNEL1, 0);
  setLEDBrightness(LEDC_CHANNEL2, 0);
  setLEDBrightness(LEDC_CHANNEL3, 0);
  delay(3000);
  setLEDBrightness(LEDC_CHANNEL1, 0);
  setLEDBrightness(LEDC_CHANNEL2, 0);
  setLEDBrightness(LEDC_CHANNEL3, 0);
  setMotorSpeed(75);
  delay(2000);
  setMotorSpeed(0);
  delay(1000);
  setMotorSpeed(-75);
  delay(2000);
  setMotorSpeed(0);
  ServoTest();
}

void setup()
{
  Serial.begin(115200);
  setupSteeringServo();
  setupLCD();
  setupLED();
  setupMCPWM();
  setupwifi();
  setupthSensor();
  testall();
  drawScreen();
}

void loop()
{
  readDht();
  float test = dht.readTemperature();
  drawScreen2(test);
  float test2 = readHumidity();
  drawScreen3(test2);
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n')
        {

          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("<p style=\"font-size:300%;\">");

            client.print("Click <a href=\"/Forward\">here</a> to Forward<br>");
            client.print("Click <a href=\"/Forward1\">here</a> to Forward<br>");
            client.print("Click <a href=\"/Forward2\">here</a> to Forward<br>");
            client.print("Click <a href=\"/Backward\">here</a> to Backward<br>");
            client.print("Click <a href=\"/Test\">here</a> to Test<br>");
            client.print("Click <a href=\"/led\">here</a> to led<br>");
            client.print("Click <a href=\"/servo\">here</a> to servo<br>");
            client.print("Click <a href=\"/servoTurnLeft\">here</a> to servoTurnLeft<br>");
            client.print("Click <a href=\"/servoTurnRight\">here</a> to servoTurnRight<br>");
            client.print("Click <a href=\"/servoTo90\">here</a> to servoTo90<br>");
            client.print("Click <a href=\"/Stop\">here</a> to Stop<br>");
            client.print(stringstatus);
            client.print("</p>");
            client.println();

            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /Forward"))
        {
          Serial.println("Forward");
          setMotorSpeed(75);
        }
        if (currentLine.endsWith("GET /Forward1"))
        {

          Serial.println("Forward");
          setMotorSpeed(50);
        }
        if (currentLine.endsWith("GET /Forward2"))
        {

          Serial.println("Forward");
          setMotorSpeed(25);
        }
        if (currentLine.endsWith("GET /Backward"))
        {

          Serial.println("Backward");
          setMotorSpeed(-50);
        }
        if (currentLine.endsWith("GET /Test"))
        {
          Serial.println("Test");
          setMotorSpeed(0);
          setMotorSpeed(25);
          delay(1000);
          setMotorSpeed(-25);
          delay(1000);
          setMotorSpeed(0);
        }
        if (currentLine.endsWith("GET /led"))
        {
          Serial.println("TestLed");
          fadeEffect(LEDC_CHANNEL1);
          fadeEffect(LEDC_CHANNEL2);
          fadeEffect(LEDC_CHANNEL3);
          delay(5000);
          setLEDBrightness(LEDC_CHANNEL1, 0);
          setLEDBrightness(LEDC_CHANNEL2, 0);
          setLEDBrightness(LEDC_CHANNEL3, 0);
        }
        if (currentLine.endsWith("GET /servo"))
        {

          Serial.println("servo");
          ServoTest();
        }
        if (currentLine.endsWith("GET /servoTurnLeft"))
        {

          Serial.println("TurnLeft");
          turnLeft();
        }
        if (currentLine.endsWith("GET /servoTurnRight"))
        {

          Serial.println("servo");
          turnRight();
        }
        if (currentLine.endsWith("GET /servoTo90"))
        {

          Serial.println("servo");
          servoStop();
        }
        if (currentLine.endsWith("GET /Stop"))
        {
          Serial.println("Stop");
          setMotorSpeed(0);
          servoStop();
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
