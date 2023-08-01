/* 8x16 I2C Eye Board */

#include "abstract/I2C_Renderer.h"
#include "../sprites/Eye_Sprites.h"

/**
 * @brief Renderer for the I2C 8x16 eye boards
 */
class Eye_Renderer : public I2C_Renderer
{
private:
  /// @brief Control object for left side 8x16 I2C eye board
  Adafruit_8x16matrix leftEyeMatrix = Adafruit_8x16matrix();

  /// @brief Control object for right side 8x16 I2C eye board
  Adafruit_8x16matrix rightEyeMatrix = Adafruit_8x16matrix();

  /// @brief Time, in milliseconds, at which the last sprite was rendered to the eye boards
  unsigned long lastRender = millis();

  /// @brief Current sprite for the eye boards
  int currentSpriteIndex = EYE_EXPRESSION_FIRST;

  /**
   * @brief Return the current sprite from PROGMEM based upon the current sprite index
   */
  inline const uint8_t *getSprite()
  {
    return getEyeSprite(currentSpriteIndex);
  }

  /**
   * @brief Update the sprite periodically, based upon the value in I2C_DEFAULT_SPRITE_DWELL_TIME
   * @sa I2C_Config.h
   */
  inline void updateSprite()
  {
    if (millis() - lastRender > I2C_DEFAULT_SPRITE_DWELL_TIME)
    {
      currentSpriteIndex++;
      if (currentSpriteIndex > EYE_EXPRESSION_LAST)
      {
        currentSpriteIndex = EYE_EXPRESSION_FIRST;
      }
      lastRender = millis();
    }
  }

public:
  /**
   * @brief Default constructor using Adafruit_8x16matrix boards to instantiate base class
   */
  Eye_Renderer() : I2C_Renderer(&leftEyeMatrix, &rightEyeMatrix)
  {
  }

  /**
   * @brief Setup the I2C control objects; should be called from arduino setup()
   * @sa leftEyeMatrix
   * @sa rightEyeMatrix
   */
  inline void setup_I2C()
  {
    setup_I2C_Addresses(I2C_ADDRESS_LEFT_EYE_BOARD, I2C_ADDRESS_RIGHT_EYE_BOARD);
    setBrightness(I2C_DEFAULT_BRIGHTNESS);
  }
};