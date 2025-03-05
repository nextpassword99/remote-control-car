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

    server.on("forward", handleMoveForward);
    server.on("backward", handleMoveBackward);
    server.on("left", handleMoveLeft);
    server.on("right", handleMoveRight);

    server.begin()
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