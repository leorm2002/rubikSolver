#include <Stepper.h>
#include <Servo.h>

int arraySize;
String letters = "";
Stepper cubo(2048, 11, 9, 10, 8);
Servo braccio;
void setup() {
  Serial.begin(9600);
  Serial.print("Ready");
  cubo.setSpeed(10);
  braccio.attach(12);
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
  }
  else if (msg == "front") {
    giraCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    giraCubo();
    giraCubo();

  }
  else if (msg == "left") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();

    ruotaFondo(90);

    }
    else if (msg == "right") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    ruotaFondo(-90);
  }
  else if (msg == "bottom") {
    giraCubo();
    giraCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    giraCubo();

  }
  else if (msg == "back") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    Serial.print("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
  }
  else if (msg == "D") {
    bloccaCubo();
    ruotaFondo(90);
  }
  else if (msg == "T") {
    cuboLibero();
    giraCubo();
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    giraCubo();
    giraCubo();
  }
  else if (msg == "F") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    cuboLibero();
    giraCubo();

  }
  else if (msg == "R") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);

    giraCubo();
    ruotaFondo(90);

  }
  else if (msg == "L") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);

    giraCubo();
    ruotaFondo(-90);
  }
  else if (msg == "B") {
    cuboLibero();
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    giraCubo();
    ruotaFondo(180);
  }
  else if (msg == "D'") {
    bloccaCubo();
    ruotaFondo(-90);
  }
  else if (msg == "T'") {
    cuboLibero();
    giraCubo();
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    giraCubo();
    giraCubo();
  }
  else if (msg == "F'") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    cuboLibero();
    giraCubo();

  }
  else if (msg == "R'") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);

    giraCubo();
    ruotaFondo(90);

  }
  else if (msg == "L'") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);

    giraCubo();
    ruotaFondo(-90);
  }
  else if (msg == "B'") {
    cuboLibero();
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    giraCubo();
    ruotaFondo(180);
  }
}




void bloccaCubo() {
  braccio.write(50);
}

void cuboLibero() {
  braccio.write(30);

}
void giraCubo() {
  braccio.write(110);
  delay(100);
  braccio.write(30);

}

void ruotaFondo(int gradi ) {
  cubo.step(map(gradi, 0, 360, 0, 2048));
  delay(1000);
}
