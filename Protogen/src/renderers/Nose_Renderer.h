/* 8x8 I2C Board */

#include "abstract/I2C_Renderer.h"
#include "../sprites/Nose_Sprites.h"

#define SPI_LED_ON 1

class Nose_Renderer : I2C_Renderer
{
private:
  /// @brief Control object for the left I2C 8x8 Nose Board
  Adafruit_8x8matrix leftNoseMatrix = Adafruit_8x8matrix();

  /// @brief Control object for the right I2C 8x8 Nose Board
  Adafruit_8x8matrix rightNoseMatrix = Adafruit_8x8matrix();

  /// @brief Time, in milliseconds, at which the last sprite was renderered to the nose boards
  unsigned long lastRender = millis();

  /// @brief Current sprite for the nose board
  int currentSpriteIndex = NOSE_EXPRESSION_FIRST;

  /**
   * @brief Return the current sprite from PROGMEM based upon the current sprite index
   * @sa Nose_Renderer::currentSpriteIndex
   */
  inline const uint8_t *getSprite()
  {
    return getNoseSprite(currentSpriteIndex);
  }

  /**
   * @brief Update the sprite periodically, based upon the value in I2C_DEFAULT_SPRITE_DWELL_TIME
   * @sa Nose_Renderer::lastRender
   * @sa Nose_Renderer::currentSpriteIndex
   * @sa I2C_Config.h
   */
  inline void updateSprite()
  {
    if (millis() - lastRender > I2C_DEFAULT_SPRITE_DWELL_TIME)
    {
      currentSpriteIndex++;
      if (currentSpriteIndex > NOSE_EXPRESSION_LAST)
      {
        currentSpriteIndex = NOSE_EXPRESSION_FIRST;
      }
      lastRender = millis();
    }
  }

public:
  Nose_Renderer() : I2C_Renderer(&leftNoseMatrix, &rightNoseMatrix)
  {
  }

  inline void setup_I2C()
  {
    setup_I2C_Addresses(I2C_ADDRESS_LEFT_NOSE_BOARD, I2C_ADDRESS_RIGHT_NOSE_BOARD);
  }

  inline void main_I2C()
  {
    schedule_Main_Thread();
  }
};