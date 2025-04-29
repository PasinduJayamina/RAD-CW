#include <Servo.h>

// Movement motor driver pins
#define MOVE_ENA 3
#define MOVE_ENB 11
#define MOVE_IN1 5
#define MOVE_IN2 6
#define MOVE_IN3 9
#define MOVE_IN4 10

// Seed dispenser motor pins
#define DISPENSE_IN1 7
#define DISPENSE_IN2 8
#define DISPENSE_ENA 12

// Servo for digging
#define DIG_SERVO_PIN 4

Servo digServo;

void setup() {
  // Initialize motor pins
  pinMode(MOVE_ENA, OUTPUT);
  pinMode(MOVE_ENB, OUTPUT);
  pinMode(DISPENSE_ENA, OUTPUT);
  pinMode(MOVE_IN1, OUTPUT);
  pinMode(MOVE_IN2, OUTPUT);
  pinMode(MOVE_IN3, OUTPUT);
  pinMode(MOVE_IN4, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(DISPENSE_IN1, OUTPUT);
  pinMode(DISPENSE_IN2, OUTPUT);

  digServo.attach(DIG_SERVO_PIN);

  Serial.begin(9600); // Bluetooth communication
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'F': moveAhead(); break;
      case 'B': moveBack(); break;
      case 'L': rotateLeft(); break;
      case 'R': rotateRight(); break;
      case 'S': haltMotors(); break;
      case 'H': digHole(); break;
      case 'D': releaseSeed(); break;
      case 'T': blinkLED(); break;
    }
  }
}

void moveAhead() {
  digitalWrite(MOVE_IN1, 1);
  digitalWrite(MOVE_IN2, 0);
  digitalWrite(MOVE_IN3, 1);
  digitalWrite(MOVE_IN4, 0);
  analogWrite(MOVE_ENA, 50);
  analogWrite(MOVE_ENB, 50);
}

void moveBack() {
  digitalWrite(MOVE_IN1, 0);
  digitalWrite(MOVE_IN2, 1);
  digitalWrite(MOVE_IN3, 0);
  digitalWrite(MOVE_IN4, 1);
  analogWrite(MOVE_ENA, 50);
  analogWrite(MOVE_ENB, 50);
}

void rotateLeft() {
  digitalWrite(MOVE_IN1, 0);
  digitalWrite(MOVE_IN2, 1);
  digitalWrite(MOVE_IN3, 1);
  digitalWrite(MOVE_IN4, 0);
  analogWrite(MOVE_ENA, 50);
  analogWrite(MOVE_ENB, 50);
}

void rotateRight() {
  digitalWrite(MOVE_IN1, 1);
  digitalWrite(MOVE_IN2, 0);
  digitalWrite(MOVE_IN3, 0);
  digitalWrite(MOVE_IN4, 1);
  analogWrite(MOVE_ENA, 50);
  analogWrite(MOVE_ENB, 50);
}

void haltMotors() {
  digitalWrite(MOVE_IN1, 0);
  digitalWrite(MOVE_IN2, 0);
  digitalWrite(MOVE_IN3, 0);
  digitalWrite(MOVE_IN4, 0);
}

void digHole() {
  digServo.write(90); // Lower
  delay(1000);
  digServo.write(0);  // Raise
}

void releaseSeed() {
  digitalWrite(DISPENSE_IN1, 1);
  digitalWrite(DISPENSE_IN2, 0);
  analogWrite(DISPENSE_ENA, 50);
  delay(500);
  digitalWrite(DISPENSE_IN1, 0);
  digitalWrite(DISPENSE_IN2, 0);
}

void blinkLED() {
  digitalWrite(13, 0);
  delay(500);
  digitalWrite(13, 1);
  delay(500);
  digitalWrite(13, 0);
  delay(500);
  digitalWrite(13, 1);
  delay(500);
}
