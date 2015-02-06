#include <SPI.h>
#include <TCL.h>

int ledPin = 13;
int stage = 0;

void setup() {
  TCL.begin();
  TCL.setupDeveloperShield();
}

void loop() {
    TCL.sendEmptyFrame();
    for (int i=0; i<150; i++) {
       TCL.sendColor(analogRead(TCL_POT1)/15,analogRead(TCL_POT2)/8,analogRead(TCL_POT3)/8);
    }
    TCL.sendEmptyFrame();
    delay(2);
}
