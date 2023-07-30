/* 8x16 I2C Eye Board */

#include "abstract/I2C_Renderer.h"
#include "../sprites/Eye_Sprites.h"

class Eye_Renderer : I2C_Renderer
{
private:
  // Control object for I2C 8x16 Eye Board
  Adafruit_8x16matrix leftEyeMatrix = Adafruit_8x16matrix();
  Adafruit_8x16matrix rightEyeMatrix = Adafruit_8x16matrix();
  unsigned long lastSpriteChange = millis();

  // Current eye sprite
  int currentSpriteIndex = EYE_EXPRESSION_FIRST;

  inline const uint8_t *getSprite()
  {
    return getEyeSprite(currentSpriteIndex);
  }

  inline void updateSprite()
  {
    if (millis() - lastSpriteChange > I2C_DEFAULT_SPRITE_DWELL_TIME)
    {
      currentSpriteIndex++;
      if (currentSpriteIndex > EYE_EXPRESSION_LAST)
      {
        currentSpriteIndex = EYE_EXPRESSION_FIRST;
      }
      lastSpriteChange = millis();
    }
  }

public:
  Eye_Renderer() : I2C_Renderer(&leftEyeMatrix, &rightEyeMatrix)
  {
  }

  inline void setup_I2C()
  {
    setup_I2C_Addresses(I2C_ADDRESS_LEFT_EYE_BOARD, I2C_ADDRESS_RIGHT_EYE_BOARD);
  }

  inline void main_I2C()
  {
    schedule_Main_Thread();
  }
};