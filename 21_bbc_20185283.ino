// Arduino pin assignment
#include <Servo.h>

#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10

Servo myservo;
int a, b; // unit: mm

#define _DUTY_MIN 553 // servo full clockwise position (180 degree)
#define _DUTY_NEU 1179 // servo neutral position (90 degree)
#define _DUTY_MAX 2200 // servo full counterclockwise position (0 degree)


#define _DIST_MIN 100 // minimum distance to be measured (unit: mm)
#define _DIST_MAX 450 // maximum distance to be measured (unit: mm)

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  
// initialize serial port
  Serial.begin(57600);
  a = 85;
  b = 346;

// initialize servo
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_NEU);
  Serial.begin(57600); 
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  //if(val < _DIST_MIN || val > _DIST_MAX) return; // return when out of range.
  return val;
}


void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a) + 50;
  
  
  if(dist_cali > 255.0) {
    myservo.writeMicroseconds(1100);
    delay(100);
  }
  else {
    myservo.writeMicroseconds(1250);
    delay(100);
  }


  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);


}
