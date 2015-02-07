#include <SPI.h>
#include <TCL.h>

int ledPin = 13;
int stage = 0;
int buffer[3][8][11] = {0};

void sendColor(int r, int g, int b) {
  if (r > 256) {
    r = 256;
  }
  if (g > 256) {
    g = 256;
  }
  if (b > 256) {
    b = 256;
  }
  if (r < 0) {
    r = 0;
  }
  if (g < 0) {
    g = 0;
  }
  if (b < 0) {
    b = 0;
  }
  TCL.sendColor(r/4, g/2, b/2);
}

void setColor(int x, int y, int r, int g, int b) {
  buffer[0][x][y] = r;
  buffer[1][x][y] = g;
  buffer[2][x][y] = b;
}

void sendFrame() {
  TCL.sendEmptyFrame();
  for (int i=0; i<100; i++) {
    if (i % 25 == 0 || i % 25 == 24 || i % 25 == 23) {
      sendColor(0x00, 0x00, 0x00);
    } else {
      int adjustedI = i-(i/25*3)-1;
      int x = adjustedI / 11;
      int y = adjustedI % 11;
      if (adjustedI % 22 < 11) {
        y = 10-y;
      }
      sendColor(buffer[0][x][y], buffer[1][x][y], buffer[2][x][y]);
    }
  }
  TCL.sendEmptyFrame();
}

void setup() {
  TCL.begin();
  TCL.setupDeveloperShield();
}

void loop() {
  stage+=analogRead(TCL_POT1)/25;
  if (stage > 1530) {
    stage = 0;
  }
  for (int i1 = 0; i1 < 8; i1++) {
    for (int i2 = 0; i2 < 11; i2++) {
      int num = (stage+((i1+i2)*(analogRead(TCL_POT2)/25))) % 1530;
      if (num <= 255) {
        setColor(i1, i2, 255,num-0,0);
      } else if (num <= 510) {
        setColor(i1, i2, 510-num,255,0);
      } else if (num <= 765) {
        setColor(i1, i2, 0, 255, num-510);
      } else if (num <= 1020) {
        setColor(i1, i2, 0, 1020-num, 255);
      } else if (num <= 1275) {
        setColor(i1, i2, num-1020, 0, 255);
      } else {
        setColor(i1, i2, 255, 0, 1530-num);
      }
    }
  }
  sendFrame();
  delay(30);
}
