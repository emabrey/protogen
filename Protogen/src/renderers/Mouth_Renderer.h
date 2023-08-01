/* 8x32 SPI Board */

#include <MD_MAX72xx.h>
#include <protothreads.h>
#include "abstract/MD_MAX72XX_GFX.h"
#include "../SPI_Config.h"

/**
 * @brief Renderer for the SPI 8x32 mouth boards
 * TODO: add the right mouth board to the SPI daisy chain and implement in software
 */
class Mouth_Renderer
{
private:
  /// @brief Control object for left side 8x32 SPI Mouth board
  MD_MAX72XX leftMouthMatrix = MD_MAX72XX(SPI_HARDWARE_TYPE, SPI_CHIP_SEL_PIN, SPI_MAX_DEVICES);

  /// @brief Graphics object for left side 8x32 SPI Mouth board
  MD_MAX72XX_GFX leftMouthGraphics = MD_MAX72XX_GFX(&leftMouthMatrix);

  /// @brief Protothread state for SPI boards
  pt spiState;

  /// @brief Time, in milliseconds, at which the last sprite was rendered to the mouth boards
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
        leftMouthMatrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
        leftMouthGraphics.fillRect(0, 0, SPI_MOUTH_HEIGHT, SPI_MOUTH_WIDTH, MD_MAX72XX::ON);
        leftMouthGraphics.drawLine(0, 0, SPI_MOUTH_HEIGHT, SPI_MOUTH_WIDTH, MD_MAX72XX::OFF);
        leftMouthMatrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        lastRender = millis();
      }

      PT_YIELD(pt);
    }

    PT_END(pt);
  }

public:
  /**
   * @brief Setup the SPI control objects; should be called from arduino setup()
   * @sa Mouth_Renderer::leftMouthMatrix
   */
  inline void setup_SPI()
  {
    leftMouthMatrix.begin();
    leftMouthMatrix.control(MD_MAX72XX::INTENSITY, SPI_MOUTH_DEFAULT_BRIGHTNESS);
    PT_INIT(&spiState);
  }

  /**
   * @brief Schedule the SPI main thread to be run
   * @sa Mouth_Renderer::spi_thread(struct pt)
   */
  inline void main_SPI()
  {
    PT_SCHEDULE(spi_Thread(&spiState));
  }
};
