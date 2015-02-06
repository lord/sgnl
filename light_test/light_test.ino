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
    stage+=analogRead(TCL_POT1)/25;
    if (stage > 765) {
      stage = 0;
    }
    for (int i=0; i<150; i++) {
      int num = (stage+(i*(analogRead(TCL_POT2)/25))) % 765;
      if (num <= 255) {
        TCL.sendColor(255-num,num,0);
      } else if (num <= 510) {
        TCL.sendColor(0,510-num,num-255);
      } else {
        TCL.sendColor(num-510,0,765-num);
      }
    }
    TCL.sendEmptyFrame();
    delay(30);
}
