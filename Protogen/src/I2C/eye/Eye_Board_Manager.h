/* 8x16 I2C Eye Board */

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../I2C_Config.h"
#include "Eye_Expressions.h"

class Eye_Board_Manager
{

private:
  // Control object for I2C Eye Board
  Adafruit_8x16matrix leftEyeMatrix = Adafruit_8x16matrix();

  // Current eye sprite
  int currentSpriteIndex = EYE_EXPRESSION_FIRST;

  // Protothread state for I2C Eye Board
  pt i2cState;

  inline int i2c_Thread(struct pt *pt)
  {
    PT_BEGIN(pt);

    while (true)
    {
      leftEyeMatrix.clear();

      const uint8_t *currentSprite = getEyeExpression(currentSpriteIndex);

      leftEyeMatrix.drawBitmap(0, 0, currentSprite, I2C_EYE_WIDTH, I2C_EYE_HEIGHT, LED_ON);

      leftEyeMatrix.writeDisplay();

      currentSpriteIndex++;
      if (currentSpriteIndex > EYE_EXPRESSION_LAST)
      {
        currentSpriteIndex = EYE_EXPRESSION_FIRST;
      }

      PT_SLEEP(pt, I2C_EYE_REFRESH_RATE_MILLI);
    }

    PT_END(pt);
  }

public:
  inline void setBrightness(uint8_t b)
  {
    leftEyeMatrix.setBrightness(b);
  }

  inline void setup_I2C_8x16()
  {
    leftEyeMatrix.begin(I2C_ADDRESS_LEFT_EYE_BOARD);
    setBrightness(I2C_EYE_DEFAULT_BRIGHTNESS);
    PT_INIT(&i2cState);
  }

  inline void main_I2C_8x16()
  {
    PT_SCHEDULE(i2c_Thread(&i2cState));
  }
};