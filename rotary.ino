#include <AccelStepper.h>
#define stepPin1 8
#define stepPin2 9
#define stepPin3 10
#define stepPin4 11
AccelStepper myStepper(stepPin1, stepPin3, stepPin2, stepPin4);
const int encoderPinA = 2;
const int encoderPinB = 3;
volatile int encoderValue = 0;
int lastEncoderValue = 0;
int motorSpeed = 0;

void setup() {
  myStepper.setMaxSpeed(300);
  myStepper.setAcceleration(500);
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
}

void loop() {
  motorSpeed = encoderValue * 10; 
  motorSpeed = constrain(motorSpeed, -1000, 1000); 
  myStepper.setSpeed(motorSpeed);
  myStepper.runSpeed();
  if (encoderValue != lastEncoderValue) {
    Serial.print("Encoder Value: ");
    Serial.print(encoderValue);
    Serial.print(" | Motor Speed: ");
    Serial.println(motorSpeed);
    lastEncoderValue = encoderValue;
  }
}

void updateEncoder() {
  int stateA = digitalRead(encoderPinA);
  int stateB = digitalRead(encoderPinB);

  if (stateA == HIGH) {
    if (stateB == LOW) {
      encoderValue++;
    } else {
      encoderValue--;
    }
  } else {
    if (stateB == HIGH) {
      encoderValue++;
    } else {
      encoderValue--;
    }
  }
}
