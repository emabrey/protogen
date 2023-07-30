/* 8x8 I2C Board */

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../I2C_Config.h"
#include "Nose_Expressions.h"

class Nose_Board_Manager
{
private:
  // Control object for I2C 8x8 Nose Board
  Adafruit_8x8matrix leftNoseMatrix = Adafruit_8x8matrix();
  Adafruit_8x8matrix rightNoseMatrix = Adafruit_8x8matrix();

  // Current nose sprite
  int currentSpriteIndex = NOSE_EXPRESSION_FIRST;

  // Protothread state for I2C Nose Board
  pt i2cNoseState;

  inline int i2c_Thread(struct pt *pt)
  {
    PT_BEGIN(pt);

    while (true)
    {
      leftNoseMatrix.clear();
      rightNoseMatrix.clear();

      const uint8_t *currentSprite = getNoseExpression(currentSpriteIndex);

      leftNoseMatrix.drawBitmap(0, 0, currentSprite, I2C_NOSE_WIDTH, I2C_NOSE_HEIGHT, LED_ON);
      rightNoseMatrix.drawBitmap(0, 0, currentSprite, I2C_NOSE_WIDTH, I2C_NOSE_HEIGHT, LED_ON);

      leftNoseMatrix.writeDisplay();
      rightNoseMatrix.writeDisplay();

      currentSpriteIndex++;
      if (currentSpriteIndex > NOSE_EXPRESSION_LAST)
      {
        currentSpriteIndex = NOSE_EXPRESSION_FIRST;
      }

      PT_SLEEP(pt, I2C_NOSE_REFRESH_RATE_MILLI);
    }

    PT_END(pt);
  }

public:
  inline void setup_I2C_8x8()
  {
    leftNoseMatrix.begin(I2C_ADDRESS_LEFT_NOSE_BOARD);
    rightNoseMatrix.begin(I2C_ADDRESS_RIGHT_NOSE_BOARD);

    leftNoseMatrix.setBrightness(I2C_NOSE_DEFAULT_BRIGHTNESS);
    rightNoseMatrix.setBrightness(I2C_NOSE_DEFAULT_BRIGHTNESS);

    PT_INIT(&i2cNoseState);
  }

  inline void main_I2C_8x8()
  {
    PT_SCHEDULE(i2c_Thread(&i2cNoseState));
  }
};