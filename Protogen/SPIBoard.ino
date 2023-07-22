/* 32x4 SPI Board */
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define SPI_HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SPI_MAX_DEVICES 4
#define SPI_CHIP_SEL_PIN 8

static MD_Parola spiMatrix = MD_Parola(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

void setup_SPI_32x4() {
  spiMatrix.begin();
  spiMatrix.setIntensity(0);
  spiMatrix.displayClear();
  spiMatrix.displayText("Hello World!!! ", PA_CENTER, 75, 0, PA_SCROLL_LEFT);
}

void main_SPI_32x4() {
  if (spiMatrix.displayAnimate()) {
    spiMatrix.displayReset();
  }
}