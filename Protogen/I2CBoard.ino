/* 8x8 I2C Board */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "protothreads.h"

#define I2C_REFRESH_RATE_MILLI 500

static const uint8_t PROGMEM
  smile_bmp[] = { B00111100,
                  B01000010,
                  B10100101,
                  B10000001,
                  B10100101,
                  B10011001,
                  B01000010,
                  B00111100 },
  frown_bmp[] = { B00111100,
                  B01000010,
                  B10100101,
                  B10000001,
                  B10011001,
                  B10100101,
                  B01000010,
                  B00111100 };

//Control object for I2C Board
static Adafruit_8x8matrix i2cMatrix = Adafruit_8x8matrix();

//Status flag for which smiley to show
static bool i2cFlipFlop = true;

//Protothread state
static pt i2cState;

void setup_I2C_8x8() {
  i2cMatrix.begin(0x70);
  i2cMatrix.setBrightness(5);
  PT_INIT(&i2cState);
}

int i2c_Thread(struct pt* pt) {
  PT_BEGIN(pt);

  // Loop forever
  for (;;) {
    i2cMatrix.clear();

    if (i2cFlipFlop) {
      i2cMatrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
    } else {
      i2cMatrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
    }

    i2cMatrix.writeDisplay();
    i2cFlipFlop = !i2cFlipFlop;
    PT_SLEEP(pt, I2C_REFRESH_RATE_MILLI);
  }

  PT_END(pt);
}

void main_I2C_8x8() {
  PT_SCHEDULE(i2c_Thread(&i2cState));
}