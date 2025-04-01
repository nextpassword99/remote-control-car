#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Servo.h>

const char *ssid = "System32";
const char *password = "edisonp21";

Servo servo;
WebSocketsServer webSocket(81);

int motorA_IN1 = 5;
int motorA_IN2 = 4;
int motorA_ENA = 0;

int servoPin = 2;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());

    setupPins();
    servo.attach(servoPin);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop()
{
    webSocket.loop();
}

void setupPins()
{
    pinMode(motorA_IN1, OUTPUT);
    pinMode(motorA_IN2, OUTPUT);
    pinMode(motorA_ENA, OUTPUT);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    if (type == WStype_TEXT)
    {
        String command = String((char *)payload);
        if (command.startsWith("forward"))
        {
            int intensity = getIntensity(command);
            moveMotorForwardBackward(HIGH, LOW, intensity);
        }
        else if (command.startsWith("backward"))
        {
            int intensity = getIntensity(command);
            moveMotorForwardBackward(LOW, HIGH, intensity);
        }
        else if (command.startsWith("left"))
        {
            int value = getIntensity(command);
            moveMotorLeftRight(value, false);
        }
        else if (command.startsWith("right"))
        {
            int value = getIntensity(command);
            moveMotorLeftRight(value, true);
        }
    }
}

int getIntensity(String command)
{
    int value = command.substring(command.indexOf(" ") + 1).toInt();
    return constrain(value, 0, 255);
}

void moveMotorLeftRight(int value, bool side)
{
    int angle = side ? map(value, 0, 250, 90, 180) : map(value, 0, 250, 90, 0);
    servo.write(angle);
}

void moveMotorForwardBackward(int in1State, int in2State, int speed)
{
    speed = map(speed, 0, 255, 0, 1023);
    digitalWrite(motorA_IN1, in1State);
    digitalWrite(motorA_IN2, in2State);
    analogWrite(motorA_ENA, speed);
}
