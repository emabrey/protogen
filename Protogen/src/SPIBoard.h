/* 32x4 SPI Board */

/* Disable the following flags to free up flash memory within the local library copy
   of `MD_Parola.h`:  ENA_MISC, ENA_WIPE, ENA_SCAN, ENA_SCR_DIA, ENA_OPNCLS,
                      ENA_GROW, ENA_SPRITE

  This must be done in the library copy of MD_Parola.h in order to have any effect.
*/
#include <MD_Parola.h>

#define SPI_HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SPI_MAX_DEVICES 4
#define SPI_CHIP_SEL_PIN 8

static MD_Parola spiMatrix = MD_Parola(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

void setup_SPI_32x4()
{
  spiMatrix.begin(1);
  spiMatrix.setIntensity(0);
  spiMatrix.displayClear();
}

static int row = 0, col = 0;

void main_SPI_32x4()
{
  spiMatrix.getGraphicObject()->setPoint(row, col, MD_MAX72XX::ON);
  row++;
  if (row >= 8)
  {
    row = 0;
    col++;
    if (col >= 32)
    {
      col = 0;
      spiMatrix.displayClear();
    }
  }
  delay(10);
}