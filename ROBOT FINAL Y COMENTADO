#include <Servo.h>
#include <NewPing.h>

#define SERVO_PIN 3
#define TRIG 12
#define ECHO 11

#define MAX_SPEED 150
#define TURN_SPEED 200
#define DISTANCE_TO_CHECK 30

// Pines del puente H para el motor derecho
int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

// Pines del puente H para el motor izquierdo
int enableLeftMotor = 6;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

// Sensor ultrasónico (TRIG, ECHO, distancia máxima en cm)
NewPing sensor(TRIG, ECHO, 400);

// Servo que mueve el sensor para mirar a los lados
Servo servo;

// Función para obtener una lectura estable del sensor ultrasónico
int getDistance() {
  int sum = 0;

  // Se realizan varias mediciones para mejorar la estabilidad
  for (int i = 0; i < 3; i++) {
    int d = sensor.ping_cm();

    // Si no hay lectura válida, se asigna un valor alto
    if (d == 0) d = 999;

    sum += d;
    delay(10);
  }

  // Se devuelve el promedio de las lecturas
  return sum / 3;
}

void setup() {
  // Configuración de pines de los motores como salida
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Inicialización del servo y posición central
  servo.attach(SERVO_PIN);
  servo.write(90);

  // Comunicación serial para depuración
  Serial.begin(9600);
}

void loop() {
  // Lectura de la distancia frontal
  int distance = getDistance();
  Serial.println(distance);

  // Si no hay obstáculo o está lejos, el robot avanza
  if (distance == 0 || distance >= DISTANCE_TO_CHECK) {
    rotateMotor(MAX_SPEED, MAX_SPEED);
  } 
  // Si hay obstáculo, ejecuta maniobra de evasión
  else {

    // Detener motores
    rotateMotor(0, 0);
    delay(1000);

    // Retroceder un poco
    rotateMotor(-TURN_SPEED, -TURN_SPEED);
    delay(300);

    // Parar antes de decidir dirección
    rotateMotor(0, 0);
    delay(500);

    // Girar el sensor hacia la izquierda y medir distancia
    servo.write(160);
    delay(700);
    int left = getDistance();

    // Girar el sensor hacia la derecha y medir distancia
    servo.write(20);
    delay(700);
    int right = getDistance();

    // Volver el sensor al centro
    servo.write(90);
    delay(200);

    // Decidir hacia qué lado girar
    if (left > right) {
      rotateMotor(TURN_SPEED, -TURN_SPEED); // gira a la izquierda
    } else {
      rotateMotor(-TURN_SPEED, TURN_SPEED); // gira a la derecha
    }

    delay(1000);

    // Avanzar después de esquivar el obstáculo
    rotateMotor(MAX_SPEED, MAX_SPEED);
    delay(800);
  }
}

// Función para controlar los motores con velocidad y dirección
void rotateMotor(int rightSpeed, int leftSpeed) {

  // Control del motor derecho
  if (rightSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Control del motor izquierdo
  if (leftSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  // Aplicación de velocidad (PWM)
  analogWrite(enableRightMotor, abs(rightSpeed));
  analogWrite(enableLeftMotor, abs(leftSpeed));
}
