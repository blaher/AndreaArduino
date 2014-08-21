#include "Arduino.h"
#include <Servo.h>

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

Ultrasonic ultrasonic(2);
Servo myServo;

int range;
int angle;
int servo_direction;
int radar_incrament = 10;
int delay_time = 1000;

void setup() {
	Serial.print("Starting...\n");
  
	myServo.attach(7);
	Serial.begin(9600);
 
	angle = 0;
	servo_direction = 0;
	myServo.write(angle);
}

void loop() {
  ultrasonic.DistanceMeasure();
  range = ultrasonic.microsecondsToInches();
  
  Serial.print("\nrange: ");
  Serial.print(range);
  
  Serial.print(", angle: ");
  Serial.println(angle);

  if (angle>=180) {
    servo_direction = 1;
  } else if (angle<=0) {
    servo_direction = 0;
  }

  if (servo_direction) {
    angle-=radar_incrament;
  } else {
    angle+=radar_incrament;
  }
  
  myServo.write(angle);

  delay(delay_time);
}
