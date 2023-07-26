/* 32x4 SPI Board */

/* Disable the following flags to free up flash memory within the local library copy
   of `MD_Parola.h`:  ENA_MISC, ENA_WIPE, ENA_SCAN, ENA_SCR_DIA, ENA_OPNCLS,
                      ENA_GROW, ENA_SPRITE

  This must be done in the library copy of MD_Parola.h in order to have any effect.
*/
#include <MD_Parola.h>
#include <protothreads.h>

#define SPI_HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SPI_MAX_DEVICES 4
#define SPI_CHIP_SEL_PIN 8
#define SPI_ROW_MAX 8
#define SPI_COL_MAX 32
#define SPI_REFRESH_RATE_MILLI 50ul

// Control object for SPI board
static MD_Parola spiMatrix = MD_Parola(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

// Protothread state for SPI board
static pt spiState;

void setup_SPI_32x4()
{
  spiMatrix.begin(1);
  spiMatrix.setIntensity(0);
  spiMatrix.displayClear();
  PT_INIT(&spiState);
}

static int row = 0, col = 0;

const int spi_Thread(struct pt *pt)
{
  PT_BEGIN(pt);

  // Loop forever
  for (;;)
  {
    spiMatrix.getGraphicObject()->setPoint(row, col, MD_MAX72XX::ON);
    row++;
    if (row >= SPI_ROW_MAX)
    {
      row = 0;
      col++;
      if (col >= SPI_COL_MAX)
      {
        col = 0;
        spiMatrix.displayClear();
      }
    }

    PT_SLEEP(pt, SPI_REFRESH_RATE_MILLI);
  }

  PT_END(pt);
}

void main_SPI_32x4()
{
  PT_SCHEDULE(spi_Thread(&spiState));
}