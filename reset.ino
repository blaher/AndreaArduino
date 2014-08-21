#include "Arduino.h"
#include <Servo.h>

Servo servo_radar;

void setup() {
    Serial.println("Resetting...");
 
    servo_radar.attach(7);
    Serial.begin(9600);
    
    servo_radar.write(0);
}

void loop() {
  
}
