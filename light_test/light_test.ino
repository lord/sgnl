#include <SPI.h>
#include <TCL.h>

int ledPin = 13;

void setup() {
  TCL.begin();
}

void loop() {
    TCL.sendEmptyFrame();
    for (int i=0; i<150; i++) {
      TCL.sendColor(random(0x00, 0xff), random(0x00, 0xff), random(0x00, 0xff));
    }
    TCL.sendEmptyFrame();
    delay(30);
}
