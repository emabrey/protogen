
#pragma once

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../../I2C_Config.h"

class I2C_Renderer
{
protected:
    virtual const uint8_t *getSprite();
    virtual void updateSprite();

    Adafruit_LEDBackpack *leftBoard, *rightBoard;
    Adafruit_GFX *leftGraphics, *rightGraphics;

    uint8_t brightness = I2C_DEFAULT_BRIGHTNESS;
    uint8_t boardWidth, boardHeight;

    // Protothread state
    pt i2cState;

    I2C_Renderer(
        Adafruit_LEDBackpack *leftBoard, Adafruit_LEDBackpack *rightBoard,
        Adafruit_GFX *leftGraphics, Adafruit_GFX *rightGraphics,
        const uint8_t boardWidth,
        const uint8_t boardHeight)
    {
        this->leftBoard = leftBoard;
        this->rightBoard = rightBoard;
        this->leftGraphics = leftGraphics;
        this->rightGraphics = rightGraphics;
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
    }

    I2C_Renderer(Adafruit_8x16matrix *left, Adafruit_8x16matrix *right) : I2C_Renderer(left, right, left, right, 8, 16){};
    I2C_Renderer(Adafruit_8x8matrix *left, Adafruit_8x8matrix *right) : I2C_Renderer(left, right, left, right, 8, 8){};

    inline void clear()
    {
        leftBoard->clear();
        rightBoard->clear();
    }

    inline void drawMirroredSprite(const uint8_t *sprite, const uint8_t width, const uint8_t height)
    {
        leftGraphics->drawBitmap(0, 0, sprite, width, height, LED_ON);
        rightGraphics->drawBitmap(0, 0, sprite, width, height, LED_ON);
    }

    inline void flush()
    {
        leftBoard->writeDisplay();
        rightBoard->writeDisplay();
    }

    inline void setBrightness(const uint8_t b)
    {

        leftBoard->setBrightness(b);
        rightBoard->setBrightness(b);
    }

    inline virtual int i2c_Thread(struct pt *pt)
    {
        PT_BEGIN(pt);

        while (true)
        {
            clear();
            drawMirroredSprite(getSprite(), boardWidth, boardHeight);
            flush();
            updateSprite();
            PT_YIELD(pt);
        }

        PT_END(pt);
    }

    inline void setup_I2C_Addresses(const uint8_t leftI2CAddress, const uint8_t rightI2CAddress)
    {
        leftBoard->begin(leftI2CAddress);
        rightBoard->begin(rightI2CAddress);

        PT_INIT(&this->i2cState);
    }

public:
    inline void schedule_Main_Thread()
    {
        PT_SCHEDULE(i2c_Thread(&this->i2cState));
    }
};