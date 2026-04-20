int TRIG = 8;
int ECO = 9;
int LED = 10;

long DURACION;
int DISTANCIA;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  DURACION = pulseIn(ECO, HIGH);
  DISTANCIA = DURACION * 0.034 / 2;

  Serial.println(DISTANCIA);

  if (DISTANCIA <= 20 && DISTANCIA >= 0) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
  }

  delay(200);
}
