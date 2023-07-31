/* 32x4 SPI Board */

#include "abstract/MD_MAX72XX_GFX.h"
#include <MD_MAX72xx.h>
#include <protothreads.h>

#include "../SPI_Config.h"

class Mouth_Renderer
{
  using enum MD_MAX72XX::controlRequest_t;
  using enum MD_MAX72XX::controlValue_t;

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
        leftMouthMatrix.control(UPDATE, OFF);
        leftMouthGraphics.fillRect(0, 0, SPI_MOUTH_HEIGHT, SPI_MOUTH_WIDTH, ON);
        leftMouthGraphics.drawLine(0, 0, SPI_MOUTH_HEIGHT, SPI_MOUTH_WIDTH, OFF);
        leftMouthMatrix.control(UPDATE, ON);
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
    leftMouthMatrix.control(INTENSITY, SPI_MOUTH_DEFAULT_BRIGHTNESS);
    PT_INIT(&spiState);
  }

  inline void main_SPI()
  {
    PT_SCHEDULE(spi_Thread(&spiState));
  }
};
