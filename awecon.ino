#include <Arduino.h>
#include <PanasonicHeatpumpIR.h>
#include "Wire.h"
#define TMP102_I2C_ADDRESS 0x48
#define LED_PIN1 11
#define LED_PIN2 10
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
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);

    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, LOW);
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
        on_awecon(power_p, mode_p, fan_p, temp_p, vdir_p, hdir_p);
        break;
    case 'O':
        Serial.println("Awecon OFF");
        off_awecon();
        break;
        // case 'w':
        //     Serial.println("LED ON");
        //     digitalWrite(LED_PIN2, HIGH);
        //     break;
        // case 't':
        //     Serial.println("LED OFF");
        //     Serial.println(action);
        //     digitalWrite(LED_PIN2, LOW);
        //     break;
    }
}

//charからintへの変換(文字の場合は-1を出力)
int ctoi(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        return -1;
    }
}

//エアコン起動
void on_awecon(int power, int mode, int fan, int temp, int vdir, int hdir)
{
    IRSenderPWM irSender(3);
    PanasonicDKEHeatpumpIR *heatpumpIR;

    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, power, mode, fan, temp, vdir, hdir);
};

//エアコン停止
void off_awecon()
{
    IRSenderPWM irSender(3);
    PanasonicDKEHeatpumpIR *heatpumpIR;

    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
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
