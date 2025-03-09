#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "System32";
const char *password = "edisonp21";

ESP8266WebServer server(80);

int ledForward = 2;
int ledBackward = 12;
int ledLeft = 4;
int ledRight = 5;

int motorA_IN1 = 13;
int motorA_IN2 = 15;
int motorA_ENA = 14;

void setup()
{
    Serial.begin(115200);
    connectionWiFi();

    setupPins();
    setupWebServer();

    server.begin();
}

void loop()
{
    server.handleClient();
}

void connectionWiFi()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}

void setupPins()
{
    pinMode(ledForward, OUTPUT);
    pinMode(ledBackward, OUTPUT);
    pinMode(ledRight, OUTPUT);
    pinMode(ledLeft, OUTPUT);

    pinMode(motorA_IN1, OUTPUT);
    pinMode(motorA_IN2, OUTPUT);
    pinMode(motorA_ENA, OUTPUT);

    pinMode(motorB_IN1, OUTPUT);
    pinMode(motorB_IN2, OUTPUT);
    pinMode(motorB_ENA, OUTPUT);
}

void setupWebServer()
{
    server.on("/forward", HTTP_GET, handleMoveForward);
    server.on("/backward", HTTP_GET, handleMoveBackward);
    server.on("/left", HTTP_GET, handleMoveLeft);
    server.on("/right", HTTP_GET, handleMoveRight);
}

void handleMoveForward()
{
    int intensity = getIntensity();
    setLed(ledForward, intensity);
    setLed(ledBackward, 0);

    moveMotorForwardBackward(HIGH, LOW, intensity, false);

    server.send(200, "text/plain", "Moving forward");
}

void handleMoveBackward()
{
    int intensity = getIntensity();
    setLed(ledBackward, intensity);
    setLed(ledForward, 0);

    moveMotorForwardBackward(LOW, HIGH, intensity, false);

    server.send(200, "text/plain", "Moving backward");
}

void handleMoveLeft()
{
    int intensity = getIntensity();
    setLed(ledLeft, intensity);
    setLed(ledRight, 0);
    server.send(200, "text/plain", "Moving left");
}

void handleMoveRight()
{
    int intensity = getIntensity();
    setLed(ledRight, intensity);
    setLed(ledLeft, 0);
    server.send(200, "text/plain", "Moving right");
}

int getIntensity()
{
    int intensity = server.arg("value").toInt();
    return constrain(intensity, 0, 255);
}

void setLed(int pin, int intensity)
{
    analogWrite(pin, intensity);
}

void moveMotorForwardBackward(int in1State, int in2State, int speed, bool sides)
{
    speed = map(speed, 0, 255, 0, 400); // ? Definir en 400 para mejor control

    if (!sides)
    {
        digitalWrite(motorA_IN1, in1State);
        digitalWrite(motorA_IN2, in2State);
        analogWrite(motorA_ENA, speed);

        digitalWrite(motorB_IN1, in1State);
        digitalWrite(motorB_IN2, in2State);
        analogWrite(motorB_ENA, speed);
    }
}
