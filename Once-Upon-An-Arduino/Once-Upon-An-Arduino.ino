/*
The Tadpole's Promise

Team Name: Tiny Animals in Hats
Team Members: Alana, Alyssa, Jae
*/

#include <Servo.h>
Servo seasonServo; // scene 2 servo 
Servo dayServo; // scene 3 servo
Servo flyServo; // scene 4 servo
Servo tongueServo; // scene 5-1 servo
Servo eatServo; // scene 5-2 servo
int potpin= 0; //analog pin connected to potentiometer
int pos = 0; // stores servo position
int val;

#define LED_PIN 13 // analog pin connected to led

#define PIN_TO_MAGNET 4 // analog pin connected to mag

#define PIN_TO_MOTION 2
int motionStateCurr = LOW;
int motionStatePrev = LOW;

void setup() {
  pinmode(LED_PIN, OUTPUT);
  pinmode(PIN_TO_MOTION, INPUT);
  myservo.attach(9);
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  // Scene 1 - HIGH circuit / LED
  bool circuitState; // read circuit flow

  // Scene 2 - Magnet sensor / servo

  // Scene 3 - HIGH circuit / servo

  // Scene 4 - Motion sensor / servo
  motionStatePrev = motionStateCurr; // restore old state
  motionStateCurr = digitalRead(PIN_TO_MOTION); // read new state

  if (motionStatePrev == LOW && motionStateCurr == HIGH) { // LOW -> HIGH
    Serial.println("Motion detected");
  } else if (motionStatePrev == HIGH && motionStateCurr == LOW) { // HIGH -> LOW
    Serial.println("Motion stop");
  }

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

  // Scene 5 - LOW circuit / 2 servo
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
