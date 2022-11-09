#include <Servo.h>

// Arduino pin assignment
#define PIN_LED   9   // LED active-low

#define IR_Sensor 0
#define PIN_SERVO 10

#define _DUTY_MIN 600  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1500 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree)

#define _DIST_MIN 100     // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

#define _EMA_ALPHA 0.5

float dist_raw, dist_ema;              // distance measured unit: mm
float dist_prev = _DIST_MIN; // distance measured unit: mm

Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(1000000);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Read IR Sensor value !!!
  a_value = analogRead(IR_Sensor);
  // Convert IR sensor value into distance !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  // we need distance range filter here !!!
  if ((dist_raw < _DIST_MIN) || (dist_raw > _DIST_MAX)) {
        dist_raw = dist_prev;
        digitalWrite(PIN_LED, 1);
  }
  else {
        dist_prev = dist_raw;
        digitalWrite(PIN_LED, 0);
  }
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist_raw + (1-_EMA_ALPHA) * dist_ema;
  // map distance into duty
  duty = (dis_ema - _DIST_MIN) * (_DUTY_MAX - _DUTY_MIN) / (float)(_DIST_MAX - _DIST_MIN) + _DUTY_MIN
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("Min:");    Serial.print(_DIST_MIN);
  Serial.print(",IR:");    Serial.print(a_value);
  Serial.print(",dist:");  Serial.print(dist_raw);
  Serial.print(",ema:");   Serial.print(dist_ema);
  Serial.print(",Servo:"); Serial.print(duty);
  Serial.print(",Max:");   Serial.print(_DIST_MAX);
  Serial.println("");
}
