/* 8x16 I2C Eye Board */

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../I2C_Addresses.h"
#include "I2C_Eye_Expressions.h"

#define I2C_EYE_REFRESH_RATE_MILLI 500ul

// Control object for I2C Eye Board
static Adafruit_8x16matrix i2cEyeMatrix = Adafruit_8x16matrix();

// Current eye sprite
static int currentEyeSpriteIndex = EYE_EXPRESSION_FIRST;

// Protothread state for I2C Eye Board
static pt i2cEyeState;

void setup_I2C_8x16()
{
  i2cEyeMatrix.begin(I2C_ADDRESS_EYE_BOARD);
  i2cEyeMatrix.setBrightness(5);
  PT_INIT(&i2cEyeState);
}

int i2c_Eye_Thread(struct pt *pt)
{
  PT_BEGIN(pt);

  // Loop forever
  for (;;)
  {
    i2cEyeMatrix.clear();

    const uint8_t *currentEyeSprite = getEyeExpression(currentEyeSpriteIndex);
    i2cEyeMatrix.drawBitmap(0, 0, currentEyeSprite, 8, 16, LED_ON);
    i2cEyeMatrix.writeDisplay();
    currentEyeSpriteIndex++;
    if (currentEyeSpriteIndex > EYE_EXPRESSION_LAST)
    {
      currentEyeSpriteIndex = EYE_EXPRESSION_FIRST;
    }

    PT_SLEEP(pt, I2C_EYE_REFRESH_RATE_MILLI);
  }

  PT_END(pt);
}

void main_I2C_8x16()
{
  PT_SCHEDULE(i2c_Eye_Thread(&i2cEyeState));
}