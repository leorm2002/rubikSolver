#include <Stepper.h>
#include <Servo.h>

int arraySize;
String letters = "";
Stepper cubo(2048, 11, 9, 10, 8);
Servo braccio;
void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
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
     while (Serial.readString() != "done") {
      ;
    }
        Serial.println("ready");

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
    Serial.println("ready");


  }
  else if (msg == "left") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();

    ruotaFondo(90);
    Serial.println("ready");
    }
    else if (msg == "right") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    ruotaFondo(-90);
    Serial.println("ready");

  }
  else if (msg == "bottom") {
    giraCubo();
    giraCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    giraCubo();
    Serial.println("ready");

  }
  else if (msg == "back") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    Serial.println("done");
    while (Serial.readString() != "done") {
      ;
    }
    giraCubo();
    Serial.println("ready");

  }
  else if (msg == "D") {
    bloccaCubo();
    ruotaFondo(90);
    Serial.println("ready");
  }
  else if (msg == "T") {
    cuboLibero();
    giraCubo();
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    giraCubo();
    giraCubo();
    Serial.println("ready");
  }
  else if (msg == "F") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    cuboLibero();
    giraCubo();

    Serial.println("ready");
  }
  else if (msg == "R") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);

    giraCubo();
    ruotaFondo(90);

    Serial.println("ready");
  }
  else if (msg == "L") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);

    giraCubo();
    ruotaFondo(-90);
    Serial.println("ready");
  }
  else if (msg == "B") {
    cuboLibero();
    giraCubo();
    bloccaCubo();
    ruotaFondo(90);
    giraCubo();
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
    giraCubo();
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    giraCubo();
    giraCubo();
    Serial.println("ready");
  }
  else if (msg == "F'") {
    cuboLibero();
    ruotaFondo(180);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    cuboLibero();
    giraCubo();

    Serial.println("ready");
  }
  else if (msg == "R'") {
    cuboLibero();
    ruotaFondo(-90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);

    giraCubo();
    ruotaFondo(90);

    Serial.println("ready");
  }
  else if (msg == "L'") {
    cuboLibero();
    ruotaFondo(90);
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);

    giraCubo();
    ruotaFondo(-90);
    Serial.println("ready");
  }
  else if (msg == "B'") {
    cuboLibero();
    giraCubo();
    bloccaCubo();
    ruotaFondo(-90);
    giraCubo();
    ruotaFondo(180);
    Serial.println("ready");

  }
}




void bloccaCubo() {
  braccio.write(50);
  Serial.println("Blocco cubo");
}

void cuboLibero() {
  braccio.write(30);
  Serial.println("Cubo libero");

}
void giraCubo() {
  braccio.write(110);
  delay(100);
  braccio.write(30);
  Serial.println("Cubo girato");

}

void ruotaFondo(int gradi ) {
  cubo.step(map(gradi, 0, 360, 0, 2048));
  delay(1000);
  Serial.println("Cubo ruotato di: " + String(gradi) + " gradi");
}
