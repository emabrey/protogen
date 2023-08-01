
#pragma once

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../../I2C_Config.h"

class I2C_Renderer
{
protected:
    /**
     * @brief Return the current sprite from PROGMEM using custom criteria
     */
    virtual const uint8_t *getSprite();

    /**
     * @brief Update the sprite periodically using custom criteria
     */
    virtual void updateSprite();

    /// @brief Pointers to the control objects of both boards
    Adafruit_LEDBackpack *leftBoard, *rightBoard;

    /// @brief Pointers to the graphics objects of both boards
    Adafruit_GFX *leftGraphics, *rightGraphics;

    /// @brief The width and height of both I2C boards in pixels
    uint8_t boardWidth, boardHeight;

    /// @brief Protothread state for I2C boards
    pt i2cState;

    /**
     * @brief Fully specified constructor to create a new I2C_Renderer
     *
     * @param leftBoard The control object for the left I2C board
     * @param rightBoard The control object for the right I2C board
     * @param leftGraphics The graphics object for the left I2C board
     * @param rightGraphics The graphics object for the right I2C board
     * @param boardWidth The width of both the left and right boards in pixels
     * @param boardHeight The height of both the left and right boards in pixels
     */
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

    /**
     * @brief Convienence constructor for a new I2C_Renderer using Adafruit 8x16 backpack boards
     *
     * @param left The left board provided as an Adafruit_8x16matrix instance
     * @param right The right board provided as an Adafruit_8x16matrix instance
     */
    I2C_Renderer(Adafruit_8x16matrix *left, Adafruit_8x16matrix *right) : I2C_Renderer(left, right, left, right, 8, 16){};

    /**
     * @brief Convienence constructor for a new I2C_Renderer using Adafruit 8x8 backpack boards
     *
     * @param left The left board provided as an Adafruit_8x8matrix instance
     * @param right The right board provided as an Adafruit_8x8matrix instance
     */
    I2C_Renderer(Adafruit_8x8matrix *left, Adafruit_8x8matrix *right) : I2C_Renderer(left, right, left, right, 8, 8){};

    /**
     * @brief Clear the left and right boards display buffers
     */
    inline void clear()
    {
        leftBoard->clear();
        rightBoard->clear();
    }

    /**
     * @brief Draw the given sprite to both left and right boards display buffers
     *
     * @param sprite The PROGMEM stored sprite with the given width and the height
     * @param width The width of the given sprite
     * @param height The height of the given sprite
     */
    inline void drawMirroredSprite(const uint8_t *sprite, const uint8_t width, const uint8_t height)
    {
        leftGraphics->drawBitmap(0, 0, sprite, width, height, LED_ON);
        rightGraphics->drawBitmap(0, 0, sprite, width, height, LED_ON);
    }

    /**
     * @brief Flush the display buffers to both I2C boards
     */
    inline void flush()
    {
        leftBoard->writeDisplay();
        rightBoard->writeDisplay();
    }

    /**
     * @brief Set the brightness on both the left and right I2C boards
     *
     * @param b The brightness level to be set for the boards
     */
    inline void setBrightness(const uint8_t b)
    {

        leftBoard->setBrightness(b);
        rightBoard->setBrightness(b);
    }

    /**
     * @brief Implementation of the thread runtime for the I2C based boards.
     *
     * @param pt The Protothread state struct
     * @return int The result of the pt execution; can be PT_ENDED if the thread terminated.
     */
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

    /**
     * @brief Setup and initialize the left and right I2C boards at the given addresses
     *
     * @param leftI2CAddress The address for the left I2C board; configure by soldering pads on backpack
     * @param rightI2CAddress The address for the right I2C board; configure by soldering pads on backpack
     */
    inline void setup_I2C_Addresses(const uint8_t leftI2CAddress, const uint8_t rightI2CAddress)
    {
        leftBoard->begin(leftI2CAddress);
        rightBoard->begin(rightI2CAddress);

        PT_INIT(&this->i2cState);
    }

    /**
     * @brief Call PT_SCHEDULE using i2c_Thread method and the i2cState struct
     */
    inline void schedule_Main_Thread()
    {
        PT_SCHEDULE(i2c_Thread(&this->i2cState));
    }

public:
    /**
     * @brief Setup the I2C control objects; should be called from arduino setup()
     */
    inline virtual void setup_I2C();

    /**
     * @brief Run the I2C main thread
     * @sa i2c_Thread(struct pt)
     */
    inline virtual void main_I2C()
    {
        schedule_Main_Thread();
    }
};