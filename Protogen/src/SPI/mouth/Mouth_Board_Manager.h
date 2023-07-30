/* 32x4 SPI Board */

/* Disable the following flags to free up flash memory within the local library copy
   of `MD_Parola.h`:  ENA_MISC, ENA_WIPE, ENA_SCAN, ENA_SCR_DIA, ENA_OPNCLS,
                      ENA_GROW, ENA_SPRITE

  This must be done in the library copy of MD_Parola.h in order to have any effect.
*/

#include <Adafruit_GFX.h>
#include <MD_Parola.h>
#include <protothreads.h>
#include "../SPI_Config.h"

class Mouth_Board_Manager : Adafruit_GFX
{
private:
  // Control object for 8x32 SPI Mouth board
  MD_Parola leftMouthMatrix = MD_Parola(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

  // Protothread state for SPI board
  pt spiState;

  inline int spi_Thread(struct pt *pt)
  {
    PT_BEGIN(pt);

    while (true)
    {
      fillRect(0, 0, 8, 32, MD_MAX72XX::ON);
      drawLine(0, 0, 8, 32, MD_MAX72XX::OFF);

      PT_SLEEP(pt, SPI_REFRESH_RATE_MILLI);
    }

    PT_END(pt);
  }

public:
  Mouth_Board_Manager() : Adafruit_GFX(SPI_MOUTH_WIDTH, SPI_MOUTH_HEIGHT)
  {
  }

  inline void drawPixel(int16_t x, int16_t y, uint16_t color)
  {
    leftMouthMatrix.getGraphicObject()->setPoint((uint8_t)(x & 0x00FF), (uint8_t)(y & 0x00FF), color != 0);
  }

  inline void setup_SPI_32x4()
  {
    leftMouthMatrix.begin(SPI_ZONE_COUNT);
    leftMouthMatrix.setIntensity(SPI_MOUTH_DEFAULT_BRIGHTNESS);
    leftMouthMatrix.displayClear();
    PT_INIT(&spiState);
  }

  inline void main_SPI_32x4()
  {
    PT_SCHEDULE(spi_Thread(&spiState));
  }
};
