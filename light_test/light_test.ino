#include <SPI.h>
#include <TCL.h>

int ledPin = 13;
int stage = 0;
int buffer[3][8][11] = {0};
int x = 0;
int y = 0;

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
  x++;
  if (x >= 8) {
    x = 0;
    y++;
  }
  if (y >= 11) {
    y = 0;
  }
  for (int i1 = 0; i1 < 8; i1++) {
    for (int i2 = 0; i2 < 11; i2++) {
      if (i1 == x && i2 == y) {
        setColor(i1,i2,0xff,0xff,0xff);
      } else {
        setColor(i1,i2,0,0,0);
      }
    }
  }
  sendFrame();
  delay(30);
}
