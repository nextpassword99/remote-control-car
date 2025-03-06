#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "System32";
const char *password = "edisonp21";

ESP8266WebServer server(80);

int ledForward = 2;
int ledBackward = 12;
int ledLeft = 4;
int ledRight = 5;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    pinMode(ledForward, OUTPUT);
    pinMode(ledBackward, OUTPUT);
    pinMode(ledRight, OUTPUT);
    pinMode(ledLeft, OUTPUT);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());

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
    digitalWrite(ledForward, HIGH);
    server.send(200, "text/plain", "Moving forward");
}

void handleMoveBackward()
{
    digitalWrite(ledBackward, HIGH);
    server.send(200, "text/plain", "Moving backward");
}

void handleMoveLeft()
{
    digitalWrite(ledLeft, HIGH);
    server.send(200, "text/plain", "Moving left");
}

void handleMoveRight()
{
    digitalWrite(ledRight, HIGH);
    server.send(200, "text/plain", "Moving right");
}
