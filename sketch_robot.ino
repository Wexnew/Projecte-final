#include <Servo.h>
#include <NewPing.h>

#define SERVO_PIN 3
#define TRIG 12
#define ECHO 11

#define MAX_SPEED 150
#define TURN_SPEED 120
#define DISTANCE_TO_CHECK 30

// Motores
int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

int enableLeftMotor = 6;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

NewPing sensor(TRIG, ECHO, 400);
Servo servo;

// 🔧 función para lectura estable
int getDistance() {
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    int d = sensor.ping_cm();
    if (d == 0) d = 999;
    sum += d;
    delay(10);
  }
  return sum / 3;
}

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(90);

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();
  Serial.println(distance);

  // 🚀 SI NO hay obstáculo → avanzar
  
  if (distance <= 5 || distance >= DISTANCE_TO_CHECK) {
    rotateMotor(MAX_SPEED, MAX_SPEED);
  } 
  // 🚧 SI hay obstáculo → esquivar
  else {

    rotateMotor(0, 0);
    delay(200);

    // retroceder
    rotateMotor(-TURN_SPEED, -TURN_SPEED);
    delay(300);

    rotateMotor(0, 0);
    delay(200);

    // mirar izquierda
    servo.write(160);
    delay(400);
    int left = getDistance();

    // mirar derecha
    servo.write(20);
    delay(400);
    int right = getDistance();

    servo.write(90);
    delay(200);

    // decidir giro
    if (left > right) {
      rotateMotor(TURN_SPEED, -TURN_SPEED);
    } else {
      rotateMotor(-TURN_SPEED, TURN_SPEED);
    }

    delay(400);

    // avanzar después de esquivar
    rotateMotor(MAX_SPEED, MAX_SPEED);
    delay(800);
  }
}

// 🔧 control motores
void rotateMotor(int rightSpeed, int leftSpeed) {

  // derecha
  if (rightSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  // izquierda
  if (leftSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightSpeed));
  analogWrite(enableLeftMotor, abs(leftSpeed));
}