/* 8x8 I2C Board */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

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

//Refresh timer for I2C Board
static unsigned long i2cLastRefreshTime = millis();

//Status flag for which smiley to show
static bool i2cFlipFlop = true;

void setup_I2C_8x8() {
  i2cMatrix.begin(0x70);
  i2cMatrix.setBrightness(5);
}

static bool i2c_readyToRefresh() {
  return (unsigned long)(millis() - i2cLastRefreshTime) >= 500ul;
}

void i2c_updateRefreshTime() {
  i2cLastRefreshTime = millis();
}

void main_I2C_8x8() {
  if (i2c_readyToRefresh()) {

    i2cMatrix.clear();

    if (i2cFlipFlop) {
      i2cMatrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
    } else {
      i2cMatrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
    }

    i2cMatrix.writeDisplay();
    i2cFlipFlop = !i2cFlipFlop;
    i2c_updateRefreshTime();
  }
}