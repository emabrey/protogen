/* 8x16 I2C Eye Board */

#include "../I2C_Board_Manager_Base.h"
#include "Eye_Expressions.h"

class Eye_Board_Manager : I2C_Board_Manager_Base
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
    return getEyeExpression(currentSpriteIndex);
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
  Eye_Board_Manager() : I2C_Board_Manager_Base(&leftEyeMatrix, &rightEyeMatrix, &leftEyeMatrix, &rightEyeMatrix, I2C_EYE_WIDTH, I2C_EYE_HEIGHT)
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