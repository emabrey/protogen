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
  /// @brief Control object for left side 8x32 SPI Mouth board
  MD_MAX72XX leftMouthMatrix = MD_MAX72XX(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

  /// @brief Graphics object for left side 8x32 SPI Mouth board
  MD_MAX72XX_GFX leftMouthGraphics = MD_MAX72XX_GFX(&leftMouthMatrix, SPI_MOUTH_WIDTH, SPI_MOUTH_HEIGHT);

  /// @brief Protothread state for SPI boards
  pt spiState;

  /// @brief Time since last change in mouth boards' displays
  unsigned long lastRender = millis();

  /**
   * @brief Implementation of the thread runtime for the SPI based mouth boards.
   *
   * @param pt The Protothread state struct
   * @return int The result of the pt execution; can be PT_ENDED if the thread terminated.
   */
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
  /**
   * @brief Setup the SPI control objects; should be called from arduino setup()
   * @sa MouthRenderer::leftMouthMatrix
   */
  inline void setup_SPI()
  {
    leftMouthMatrix.begin();
    leftMouthMatrix.control(INTENSITY, SPI_MOUTH_DEFAULT_BRIGHTNESS);
    PT_INIT(&spiState);
  }

  /**
   * @brief Schedule the SPI main thread to be run
   * @sa spi_thread(struct pt)
   */
  inline void main_SPI()
  {
    PT_SCHEDULE(spi_Thread(&spiState));
  }
};
