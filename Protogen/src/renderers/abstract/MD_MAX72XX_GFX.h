
#include <Adafruit_GFX.h>
#include <MD_MAX72xx.h>
#include <protothreads.h>
#include "../../SPI_Config.h"

class MD_MAX72XX_GFX : public Adafruit_GFX
{
protected:
    MD_MAX72XX *matrix;

public:
    MD_MAX72XX_GFX(MD_MAX72XX *matrix, uint16_t width, uint16_t height) : Adafruit_GFX(width, height)
    {
        this->matrix = matrix;
    }

    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        matrix->setPoint(x, y, (color == 0) ? SPI_LED_OFF : SPI_LED_ON);
    }
};