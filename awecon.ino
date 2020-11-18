#define LED_PIN1 10

void setup()
{
    pinMode(LED_PIN1, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.println(200);
    digitalWrite(LED_PIN1, HIGH);
    delay(1000);
    digitalWrite(LED_PIN1, LOW);
    delay(1000);
}
