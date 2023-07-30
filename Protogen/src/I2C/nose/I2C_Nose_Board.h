/* 8x8 I2C Board */

#include <Adafruit_LEDBackpack.h>
#include <protothreads.h>
#include "../I2C_Addresses.h"
#include "I2C_Nose_Expressions.h"

#define I2C_NOSE_REFRESH_RATE_MILLI 500ul

// Control object for I2C 8x8 Nose Board
static Adafruit_8x8matrix i2cLeftNoseMatrix = Adafruit_8x8matrix();
static Adafruit_8x8matrix i2cRightNoseMatrix = Adafruit_8x8matrix();

// Current eye sprite
static int currentNoseSpriteIndex = NOSE_EXPRESSION_FIRST;

// Protothread state for I2C Eye Board
static pt i2cNoseState;

void setup_I2C_8x8()
{
  i2cLeftNoseMatrix.begin(I2C_ADDRESS_LEFT_NOSE_BOARD);
  i2cRightNoseMatrix.begin(I2C_ADDRESS_RIGHT_NOSE_BOARD);

  i2cLeftNoseMatrix.setBrightness(5);
  i2cRightNoseMatrix.setBrightness(5);

  PT_INIT(&i2cNoseState);
}

int i2c_Thread(struct pt *pt)
{
  PT_BEGIN(pt);

  // Loop forever
  for (;;)
  {
    i2cLeftNoseMatrix.clear();
    i2cRightNoseMatrix.clear();

    const uint8_t *currentNoseSprite = getNoseExpression(currentNoseSpriteIndex);

    i2cLeftNoseMatrix.drawBitmap(0, 0, currentNoseSprite, 8, 8, LED_ON);
    i2cRightNoseMatrix.drawBitmap(0, 0, currentNoseSprite, 8, 8, LED_ON);

    i2cLeftNoseMatrix.writeDisplay();
    i2cRightNoseMatrix.writeDisplay();

    currentNoseSpriteIndex++;
    if (currentNoseSpriteIndex > NOSE_EXPRESSION_LAST)
    {
      currentNoseSpriteIndex = NOSE_EXPRESSION_FIRST;
    }

    PT_SLEEP(pt, I2C_NOSE_REFRESH_RATE_MILLI);
  }

  PT_END(pt);
}

void main_I2C_8x8()
{
  PT_SCHEDULE(i2c_Thread(&i2cNoseState));
}