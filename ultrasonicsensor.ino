int trigpin = 9;
int echopin = 10;
void setup()
{
    Serial.begin(9600);
    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
}
void loop()
{
    long duration, distance;
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH);
    distance = (duration / 2) / 29.1;
    Serial.print(distance);
    Serial.println("CM");
    delay(10);
}