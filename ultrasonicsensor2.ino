#include <NewPing.h> // library sensor ultrasonic
#include <Servo.h>   // library motor servo

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 120

#define TRIGGER_PIN1 8
#define ECHO_PIN1 7
#define MAX_DISTANCE1 22

Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);     // NewPing setup of pins and maximum distance.
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // NewPing setup of pins and maximum distance.

void setup()
{
    Serial.begin(9600);
    myservo.attach(2);
}

void loop()
{
    delay(1500);
    int jarak = sonar.ping_cm();      // Send out the ping, get the results in centimeters.
    int kapasitas = sonar1.ping_cm(); // Send out the ping, get the results in centimeters.
    Serial.println(jarak);
    Serial.println(kapasitas);
}
