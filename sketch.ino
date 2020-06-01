
#include <Servo.h>

const int pinDirezione = 5;
const int pinStep = 6;

const int numeroStepMotore = 200; //E' il numero di step per rotazione del motore (potrebbe differire in base al modello)
const long velocita = 1500; //Si tratta di microsecondi tra un impulso e l'altro sul pin STEP

Servo braccio;
void setup() {
  pinMode(pinStep, OUTPUT);
  pinMode(pinDirezione, OUTPUT);
  braccio.attach(9);
  Serial.begin(9600);
  Serial.println("Ready");
  digitalWrite(pinDirezione, LOW);

}

void loop() {

  if (Serial.available() > 0) {
    String recieved = Serial.readString();
    switchLetter(recieved);

  }

}


void switchLetter(String msg) {
  if (msg == "top") {
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    Serial.println("ready");

  }
  else if (msg == "front") {
    ribaltaCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    ribaltaCubo();
    ribaltaCubo();
    ribaltaCubo();
    Serial.println("ready");


  }
  else if (msg == "left") {
    cuboLibero();
    ruotaFondo(-90);
    ribaltaCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    ribaltaCubo();

    ruotaFondo(90);
    Serial.println("ready");
  }
  else if (msg == "right") {
    cuboLibero();
    ruotaFondo(90);
    ribaltaCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    ribaltaCubo();
    ruotaFondo(-90);
    Serial.println("ready");

  }
  else if (msg == "bottom") {
    ribaltaCubo();
    ribaltaCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    ribaltaCubo();
    ribaltaCubo();
    Serial.println("ready");

  }
  else if (msg == "back") {
    cuboLibero();
    ruotaFondo(180);
    ribaltaCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    ribaltaCubo();
    Serial.println("ready");

  }
  else if (msg == "D") {
    bloccaCubo();
    ruotaFondo(90);
    Serial.println("ready");
  }
  else if (msg == "T") {
    cuboLibero();
    ribaltaCubo();
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(90);
    ribaltaCubo();
    ribaltaCubo();
    Serial.println("ready");
  }
  else if (msg == "F") {
    cuboLibero();
    ruotaFondo(180);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(90);
    cuboLibero();
    ribaltaCubo();

    Serial.println("ready");
  }
  else if (msg == "R") {
    cuboLibero();
    ruotaFondo(-90);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(90);

    ribaltaCubo();
    ruotaFondo(90);

    Serial.println("ready");
  }
  else if (msg == "L") {
    cuboLibero();
    ruotaFondo(90);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(90);

    ribaltaCubo();
    ruotaFondo(-90);
    Serial.println("ready");
  }
  else if (msg == "B") {
    cuboLibero();
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(90);
    ribaltaCubo();
    ruotaFondo(180);
    Serial.println("ready");
  }
  else if (msg == "D'") {
    bloccaCubo();
    ruotaFondo(-90);
    Serial.println("ready");
  }
  else if (msg == "T'") {
    cuboLibero();
    ribaltaCubo();
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(-90);
    ribaltaCubo();
    ribaltaCubo();
    Serial.println("ready");
  }
  else if (msg == "F'") {
    cuboLibero();
    ruotaFondo(180);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(-90);
    cuboLibero();
    ribaltaCubo();

    Serial.println("ready");
  }
  else if (msg == "R'") {
    cuboLibero();
    ruotaFondo(-90);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(-90);

    ribaltaCubo();
    ruotaFondo(90);

    Serial.println("ready");
  }
  else if (msg == "L'") {
    cuboLibero();
    ruotaFondo(90);
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(-90);

    ribaltaCubo();
    ruotaFondo(-90);
    Serial.println("ready");
  }
  else if (msg == "B'") {
    cuboLibero();
    ribaltaCubo();
    bloccaCubo();
    ruotaFondo(-90);
    ribaltaCubo();
    ruotaFondo(180);
    Serial.println("ready");

  }
}




void bloccaCubo() {
  braccio.write(130);
  Serial.println("Blocco cubo");
  delay(400);
}

void cuboLibero() {
  braccio.write(80);
  Serial.println("Cubo libero");
  delay(400);
}
void ribaltaCubo() {
  braccio.write(80);
  delay(500);
  int pos;
  for (pos = 80; pos <= 165; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    braccio.write(pos);              // tell servo to go to position in variable 'pos'
    delay(7);                       // waits 15ms for the servo to reach the position
  }
  braccio.write(80);
  delay(1000);
  Serial.println("Cubo girato");

}

void ruotaFondo(int deg ) {
  if (deg > 0) {
    for (int x = 0; x < map(deg, 0, 360, 0, 200); x++) {
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(velocita);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(velocita);
    }
  }
  else {
    for (int x = map(deg, 0, 360, 0, 200); x > 0; x--) {
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(velocita);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(velocita);
    }
  }
  Serial.println("Cubo ruotato di: " + String(deg) + " gradi");
  delay(200);
}
