#include <Arduino.h>
#include <PanasonicHeatpumpIR.h>
#include <MitsubishiHeavyHeatpumpIR.h>
#include "Wire.h"
int power_p;
int mode_p;
int fan_p;
int temp_p;
int vdir_p;
int hdir_p;
char setting;

void setup()
{
    // setup
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char ReaderFromNode;
        ReaderFromNode = (char)Serial.read();
        convertToState(ReaderFromNode);
    }

    Serial.println(get_temp());
    delay(1000);
}

// Arduinoの制御 NodeServerからactionが送られてくる
void convertToState(char action)
{
    int action_num;

    //actionを数値に変換
    action_num = ctoi(action);

    //actionが文字の時
    if (action_num == -1)
        setting = action;

    switch (setting)
    {
    //Power(電源)
    case 'P':
        if (action_num >= 0)
            power_p = action_num;
        break;
    //Mode(運転モード)
    case 'M':
        if (action_num >= 0)
            mode_p = action_num;
        break;
    //Fan(風量)
    case 'F':
        if (action_num >= 0)
            fan_p = action_num;
        break;
    //Temperature(温度) 20~29度
    case 'T':
        if (action_num >= 0)
            temp_p = 20 + action_num;
        break;
    //温度 16~19度
    case 't':
        if (action_num >= 0)
            temp_p = 10 + action_num;
    //VDIR(風向高さ)
    case 'V':
        if (action_num >= 0)
            vdir_p = action_num;
        break;
    //HDIR(風向左右)
    case 'H':
        if (action_num >= 0)
            hdir_p = action_num;
        break;
    //エアコン設定パラメータ全送信後
    case 'E':
        Serial.print("p:");
        Serial.print(power_p);
        Serial.print("\tm:");
        Serial.print(mode_p);
        Serial.print("\tf:");
        Serial.print(fan_p);
        Serial.print("\tt:");
        Serial.print(temp_p);
        Serial.print("\tv:");
        Serial.print(vdir_p);
        Serial.print("\th:");
        Serial.println(hdir_p);
        //エアコン起動
        on_Panasonic(power_p, mode_p, fan_p, temp_p, vdir_p, hdir_p);
        // on_MitsuHeavy(power_p, mode_p, fan_p, temp_p, vdir_p, hdir_p);
        break;
    case 'O':
        Serial.println("Awecon OFF");
        //エアコン停止
        off_Panasonic();
        // off_MitsuHeavy();
        break;
    }
}