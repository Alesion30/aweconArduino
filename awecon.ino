#define LED_PIN1 11
#define LED_PIN2 10

void setup()
{
    // setup
    Serial.begin(9600);
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);

    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, LOW);
}

void loop()
{
    if (Serial.available() > 0) // Read from serial port
    {
        char ReaderFromNode; // Store current character
        ReaderFromNode = (char)Serial.read();
        convertToState(ReaderFromNode); // Convert character to state
    }
    delay(1000);
}

void convertToState(char chr)
{
    if (chr == 'w')
    {
        Serial.println("ON");
        digitalWrite(LED_PIN2, HIGH);
    }
    if (chr == 't')
    {
        Serial.println("OFF");
        digitalWrite(LED_PIN2, LOW);
    }
}
