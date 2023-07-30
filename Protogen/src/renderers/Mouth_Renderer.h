/* 32x4 SPI Board */

#include "abstract/MD_MAX72XX_GFX.h"
#include <MD_MAX72xx.h>
#include <protothreads.h>

#include "../SPI_Config.h"

class Mouth_Renderer
{
private:
  // Control object for 8x32 SPI Mouth board
  MD_MAX72XX leftMouthMatrix = MD_MAX72XX(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

  // Graphics object for 8x32 SPI Mouth board
  MD_MAX72XX_GFX leftMouthGraphics = MD_MAX72XX_GFX(&leftMouthMatrix, SPI_MOUTH_WIDTH, SPI_MOUTH_HEIGHT);

  // Protothread state for SPI board
  pt spiState;

  unsigned long lastRender = millis();

  inline int spi_Thread(struct pt *pt)
  {
    PT_BEGIN(pt);

    while (true)
    {
      if (millis() - lastRender > SPI_DEFAULT_SPRITE_DWELL_TIME)
      {
        leftMouthMatrix.clear();
        leftMouthMatrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
        leftMouthGraphics.fillRect(0, 0, 8, 32, MD_MAX72XX::ON);
        leftMouthGraphics.drawLine(0, 0, 8, 32, MD_MAX72XX::OFF);
        leftMouthMatrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        lastRender = millis();
      }

      PT_YIELD(pt);
    }

    PT_END(pt);
  }

public:
  inline void setup_SPI()
  {
    leftMouthMatrix.begin();
    leftMouthMatrix.control(MD_MAX72XX::INTENSITY, SPI_MOUTH_DEFAULT_BRIGHTNESS);
    PT_INIT(&spiState);
  }

  inline void main_SPI()
  {
    PT_SCHEDULE(spi_Thread(&spiState));
  }
};
