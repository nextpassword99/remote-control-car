#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char *ssid = "System32";
const char *password = "edisonp21";

Servo servo;
ESP8266WebServer server(80);

int motorA_IN1 = 14;
int motorA_IN2 = 12;
int motorA_ENA = 5;

int servoPin = 2;

void setup()
{
    Serial.begin(115200);
    connectionWiFi();

    setupPins();
    setupWebServer();
    servo.attach(servoPin);

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
    pinMode(motorA_IN1, OUTPUT);
    pinMode(motorA_IN2, OUTPUT);
    pinMode(motorA_ENA, OUTPUT);
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

    moveMotorForwardBackward(LOW, HIGH, intensity);

    server.send(200, "text/plain", "Moving forward");
}

void handleMoveBackward()
{
    int intensity = getIntensity();

    moveMotorForwardBackward(HIGH, LOW, intensity);

    server.send(200, "text/plain", "Moving backward");
}

void handleMoveLeft()
{
    int value = getIntensity();

    moveMotorLeftRight(value, false);

    server.send(200, "text/plain", "Moving left");
}

void handleMoveRight()
{
    int value = getIntensity();

    moveMotorLeftRight(value, true);

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

void moveMotorLeftRight(int value, bool side)
{
    int angle;
    if (!side)
    {
        angle = map(value, 0, 250, 90, 0);
    }
    else
    {
        angle = map(value, 0, 250, 90, 180);
    }
    servo.write(angle);
}

void moveMotorForwardBackward(int in1State, int in2State, int speed)
{
    speed = map(speed, 0, 255, 0, 1023); // ? Definir en 400 para mejor control
    digitalWrite(motorA_IN1, in1State);
    digitalWrite(motorA_IN2, in2State);
    analogWrite(motorA_ENA, speed);
}
