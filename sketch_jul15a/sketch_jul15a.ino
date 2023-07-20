
//Defines for 32x4 SPI Board
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

//Defines for 8x8 I2C Board
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define SPI_HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SPI_MAX_DEVICES 4
#define SPI_CHIP_SEL_PIN 8

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

// Objects to control boards
MD_Parola spiMatrix = MD_Parola(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);
Adafruit_8x8matrix i2cMatrix = Adafruit_8x8matrix();

void setup_SPI_32x4() {
  spiMatrix.begin();
  spiMatrix.setIntensity(0);
  spiMatrix.displayClear();
  spiMatrix.displayText("Hello World!!! ", PA_CENTER, 75, 100, PA_SCROLL_LEFT);
}

void setup_I2C_8x8() {
  i2cMatrix.begin(0x70);
  i2cMatrix.setBrightness(5);
}

//Refresh timer for I2C Board
unsigned long i2cLastRefreshTime = millis();

bool i2c_readyToRefresh() {
  return (unsigned long)(millis() - i2cLastRefreshTime) >= 500ul;
}

void i2c_updateRefreshTime() {
  i2cLastRefreshTime = millis();
}

void setup() {
  setup_SPI_32x4();
  setup_I2C_8x8();
}

bool i2cFlipFlop = true;

void loop() {
  if (spiMatrix.displayAnimate()) {
    spiMatrix.displayReset();
  }

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
