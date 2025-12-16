/*
The Tadpole's Promise

Team Name: Tiny Animals in Hats
Team Members: Alana, Alyssa, Jae
*/

#include <Servo.h>
Servo seasonServo; // scene 2 servo 
Servo dayServo; // scene 3 servo
Servo flyServo; // scene 4 servo
Servo tongueServo; // scene 5 servo
int pos = 0; // stores servo position

// flyServo loop parameters
const int servoStart = 110;  // servo starting speed
const int servoStop = 90; // servo ending speed
bool triggered = false; // keeps interaction from being triggered repeatedly

#define CIRCUIT_PIN1 8 // analog pin connected to scene 1 circuit
#define CIRCUIT_PIN2 3 // analog pin connected to scene 3 circuit
#define CIRCUIT_PIN3 7 // analog pin connected to scene 5 circuit

// #define LED_PIN 13 // analog pin connected to led
const int ledOne = 13;

const int magSens = 2; // analog pin connected to mag
int magState = LOW;

const int lightSensorPin = A0; // analog pin connected to photoresistor   

int circuit1State; // read circuit flow
int circuit2State;
int circuit3State;

void setup() {
  pinMode(ledOne, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(magSens, INPUT);
  seasonServo.attach(6);
  dayServo.attach(5);
  flyServo.attach(9);
  tongueServo.attach(10);
  Serial.begin(9600);
}

void loop() {
  // Scene 1 - HIGH circuit / LED
  circuit1State = digitalRead(CIRCUIT_PIN1);
  bool circuitOn = false;
  Serial.print("circuit1State ");
  Serial.println(circuit1State);

  if (circuit1State == HIGH) {
    digitalWrite(ledOne, HIGH);
    circuitOn = true;
    Serial.print("Circuit on");
  } else {
    digitalWrite(ledOne, LOW);
    circuitOn = false;
  }

  // Scene 2 - Magnet sensor / servo
  magState = digitalRead(magSens);
  //Serial.println("magState ");
  //Serial.println(magState);

  if (magState == LOW) {
    //seasonServo.write(100); // spin forward
  } else {
    seasonServo.write(90); // stop
  }

  // Scene 3 - HIGH circuit / servo
  circuit2State = digitalRead(CIRCUIT_PIN2);

  if (circuit2State == HIGH) {
    dayServo.write(120); // spin forward
  } else {
    dayServo.write(90);
  }

  // Scene 4 - Light sensor / servo
  int lightVal = analogRead(lightSensorPin); // read photoresistor state
  //Serial.print("lightVal ");
  //Serial.println(lightVal);

  if (lightVal < 100 && circuitOn == false && triggered == false) { // HIGH -> LOW
    triggered = true;

    // Move from right to left
    for (int pos = servoStart; pos >= servoStop; pos--) {
      flyServo.write(pos);
      delay(15); // Adjust speed (smaller = faster)
    }
  }

  // Scene 5 - LOW circuit / 2 servo
  circuit3State = digitalRead(CIRCUIT_PIN3);
  //Serial.print("circuit3State ");
  //Serial.println(circuit3State);

  if (circuit3State == LOW && circuitOn == false) {
    for (pos = 0; pos <= 180; pos += 1) { // 0 degrees to 180 degrees
      tongueServo.write(pos);             
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) { // 180 degrees to 0 degrees
      tongueServo.write(pos);              
      delay(15);                       
    }                  
  }
}
