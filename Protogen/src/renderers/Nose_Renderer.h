/* 8x8 I2C Board */

#include "abstract/I2C_Renderer.h"
#include "../sprites/Nose_Sprites.h"

#define SPI_LED_ON 1

class Nose_Renderer : I2C_Renderer
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
    return getNoseSprite(currentSpriteIndex);
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