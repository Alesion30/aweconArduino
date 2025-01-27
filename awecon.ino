#include <Arduino.h>
#include <PanasonicHeatpumpIR.h>
#include <MitsubishiHeavyHeatpumpIR.h>
#include <DaikinHeatpumpIR.h>
#include <HitachiHeatpumpIR.h>
#include "Wire.h"

#define LED_PIN1 11
#define LED_PIN2 10

// 変数
int mode_p;
int fan_p;
int temp_p;
int vdir_p;
int hdir_p;
char setting;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    // LED設定
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
}

void loop()
{
    // Nodeサーバーからシリアル通信で文字列が送られてきたとき
    if (Serial.available() > 0)
    {
        char ReaderFromNode;
        ReaderFromNode = (char)Serial.read();
        convertToState(ReaderFromNode);
        // 0.05秒待つ
        delay(50);
    }
    else
    {
        // 1秒待つ
        delay(1000);
    }

    // 現在の温度を送信
    Serial.println(getTemp());
}

// Arduinoの制御 Nodeサーバーからactionが送られてくる
void convertToState(char action)
{
    int actionNum;

    // actionを数値に変換
    actionNum = convertToInt(action);

    // actionが文字の時
    if (actionNum == -1)
    {
        setting = action;
    }

    switch (setting)
    {
    case 'M': // Mode(運転モード)
        if (actionNum >= 0)
            mode_p = actionNum;
        break;
    case 'F': // Fan(風量)
        if (actionNum >= 0)
            fan_p = actionNum;
        break;
    case 'T': // Temperature(温度) 20~29度
        if (actionNum >= 0)
            temp_p = 20 + actionNum;
        break;
    case 't': // 温度 16~19度
        if (actionNum >= 0)
            temp_p = 10 + actionNum;
    case 'V': // VDIR(風向高さ)
        if (actionNum >= 0)
            vdir_p = actionNum;
        break;
    case 'H': // HDIR(風向左右)
        if (actionNum >= 0)
            hdir_p = actionNum;
        break;
    case 'E': // 設定情報をエアコンに送信
        Serial.print("m:");
        Serial.print(mode_p);
        Serial.print("\tf:");
        Serial.print(fan_p);
        Serial.print("\tt:");
        Serial.print(temp_p);
        Serial.print("\tv:");
        Serial.print(vdir_p);
        Serial.print("\th:");
        Serial.println(hdir_p);
        // controlDaikinAirConditionar(mode_p, fan_p, temp_p, vdir_p, hdir_p);
        // controlPanasonicAirConditionar(mode_p, fan_p, temp_p, vdir_p, hdir_p);
        controlMitsuHeavyAirConditionar(mode_p, fan_p, temp_p, vdir_p, hdir_p);
        // controlHitachiAirConditionar(mode_p, fan_p, temp_p, vdir_p, hdir_p);
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        break;
    case 'O': // エアコンを停止
        Serial.println("Sent a signal to the air conditioner to stop.");
        // stopDaikinAirConditionar();
        // stopPanasonicAirConditionar();
        stopMitsuHeavyAirConditionar();
        // stopHitachiAirConditionar();
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        break;
    }
}
