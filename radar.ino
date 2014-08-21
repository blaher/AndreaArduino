#include "Arduino.h"
#include <Servo.h>

int range;
int angle;
int servo_direction;
int radar_incrament = 10;
int delay_time = 1;
int ultrasonic_radar_position = 2;
int servo_radar_position = 7;

class Ultrasonic
{
    public:
        Ultrasonic(int pin);
        void DistanceMeasure(void);
        long microsecondsToCentimeters(void);
        long microsecondsToInches(void);
    private:
        int _pin;
        long duration;
};
Ultrasonic::Ultrasonic(int pin)
{
    _pin = pin;
}
void Ultrasonic::DistanceMeasure(void)
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pin,LOW);
    pinMode(_pin,INPUT);
    duration = pulseIn(_pin,HIGH);
}
long Ultrasonic::microsecondsToCentimeters(void)
{
    return duration/29/2;   
}
long Ultrasonic::microsecondsToInches(void)
{
    return duration/74/2;   
}

Ultrasonic ultrasonic_radar(ultrasonic_radar_position);
Servo servo_radar;

void setup() {
    Serial.println("Starting...");
 
    servo_radar.attach(servo_radar_position);
    Serial.begin(9600);
 
    angle = 0;
    servo_direction = 0;
    servo_radar.write(angle);
}

void loop() {
    ultrasonic_radar.DistanceMeasure();
    range = ultrasonic_radar.microsecondsToInches();
 
    Serial.print("range: ");
    Serial.print(range);
 
    Serial.print(", angle: ");
    Serial.println(angle);

    if (angle>=180) {
        servo_direction = 1;
    } else if (angle<=0) {
        servo_direction = 0;
    }

    if (servo_direction) {
        angle -= radar_incrament;
    } else {
        angle += radar_incrament;
    }
 
    servo_radar.write(angle);

    delay(delay_time);
}
