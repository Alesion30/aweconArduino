#include <Arduino.h>
#include <PanasonicHeatpumpIR.h>
#include "Wire.h"
#define TMP102_I2C_ADDRESS 0x48
#define LED_PIN1 11
#define LED_PIN2 10

void setup()
{
    // setup
    Wire.begin();
    Serial.begin(9600);
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);

    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, LOW);
}

void loop()
{
    IRSenderPWM irSender(3);
    PanasonicDKEHeatpumpIR *heatpumpIR;

    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
    delay(5000);

    // if (Serial.available() > 0)
    // {
    //     char ReaderFromNode;
    //     ReaderFromNode = (char)Serial.read();
    //     convertToState(ReaderFromNode);
    // }
    // Serial.println(get_temp());
    // digitalWrite(LED_PIN2, HIGH);
    // delay(1000);

    // digitalWrite(LED_PIN2, LOW);
    // delay(1000);
}

// Arduinoの制御 NodeServerからactionが送られてくる
void convertToState(char action)
{
    switch (action)
    {
    case 'w':
        Serial.println("LED ON");
        digitalWrite(LED_PIN2, HIGH);
        break;
    case 't':
        Serial.println("LED OFF");
        digitalWrite(LED_PIN2, LOW);
        break;
    }
}

// 温度センサを利用して、室温を取得
float get_temp()
{
    int temp_raw;
    float temp;

    Wire.beginTransmission(TMP102_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
    Wire.endTransmission();

    temp_raw = Wire.read() * 16 + Wire.read() / 16;
    temp = temp_raw * 0.0625;

    return temp;
}
