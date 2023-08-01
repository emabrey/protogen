
#include <Adafruit_GFX.h>
#include <MD_MAX72xx.h>
#include <protothreads.h>
#include "../../SPI_Config.h"
/**
 * @brief Adapter to allow MD_MAX72XX board to be drawn using Adafruit_GFX API
 */
class MD_MAX72XX_GFX : public Adafruit_GFX
{
protected:
    MD_MAX72XX *matrix;

public:
    /**
     * @brief Construct a MD_MAX72XX_GFX object that wraps around the given MD_MAX72XX instance
     *
     * @param matrix The MD_MAX72XX instance that this Adafruit_GFX implementation should draw to
     */
    MD_MAX72XX_GFX(MD_MAX72XX *matrix) : Adafruit_GFX(matrix->getColumnCount(), ROW_SIZE)
    {
        this->matrix = matrix;
    }

    /**
     * @brief Set a pixel on or off on the underlying MD_MAX72XX display.
     *
     * @param x The horizontal poisition of the pixel to change
     * @param y The vertical poisition of the pixel to change
     * @param color If zero, turn the pixel off; otherwise turn pixel to on state
     */
    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        matrix->setPoint((uint8_t)x, y, (color == 0) ? MD_MAX72XX::OFF : MD_MAX72XX::ON);
    }
};