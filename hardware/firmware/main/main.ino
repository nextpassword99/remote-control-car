#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

int ledForward = 2;
int ledBackward = 3;
int ledLeft = 4;
int ledRight = 5;

void setup()
{
    pinMode(ledForward, OUTPUT);
    pinMode(ledBackward, OUTPUT);
    pinMode(ledRight, OUTPUT);
    pinMode(ledLeft, OUTPUT);

    server.on("/forward", HTTP_GET, handleMoveForward);
    server.on("/backward", HTTP_GET, handleMoveBackward);
    server.on("/left", HTTP_GET, handleMoveLeft);
    server.on("/right", HTTP_GET, handleMoveRight);

    server.begin();
}

void loop()
{
    server.handleClient();
}

void handleMoveForward()
{
    digitalWrite(ledForward, HIGHT)
}

void handleMoveBackward()
{
    digitalWrite(ledBackward, HIGHT)
}

void handleMoveLeft()
{
    digitalWrite(ledLeft, HIGHT)
}

void handleMoveRight()
{
    digitalWrite(ledRight, HIGHT)
}