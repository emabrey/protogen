/* 8x8 I2C Board */

#include "../I2C_Board_Manager_Base.h"
#include "Nose_Expressions.h"

class Nose_Board_Manager : I2C_Board_Manager_Base
{
private:
  // Control object for I2C 8x8 Nose Board
  Adafruit_8x8matrix leftNoseMatrix = Adafruit_8x8matrix();
  Adafruit_8x8matrix rightNoseMatrix = Adafruit_8x8matrix();
  unsigned long lastSpriteChange = millis();

  // Current nose sprite
  int currentSpriteIndex = NOSE_EXPRESSION_FIRST;

  inline const uint8_t *getSprite()
  {
    return getNoseExpression(currentSpriteIndex);
  }

  inline void updateSprite()
  {
    if (millis() - lastSpriteChange > I2C_DEFAULT_SPRITE_DWELL_TIME)
    {
      currentSpriteIndex++;
      if (currentSpriteIndex > NOSE_EXPRESSION_LAST)
      {
        currentSpriteIndex = NOSE_EXPRESSION_FIRST;
      }
      lastSpriteChange = millis();
    }
  }

public:
  Nose_Board_Manager() : I2C_Board_Manager_Base(&leftNoseMatrix, &rightNoseMatrix, &leftNoseMatrix, &rightNoseMatrix, I2C_NOSE_WIDTH, I2C_NOSE_HEIGHT)
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