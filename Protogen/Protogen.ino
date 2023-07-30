/* Main Program */

#include "src/SPI/mouth/Mouth_Board_Manager.h"
#include "src/I2C/eye/Eye_Board_Manager.h"
#include "src/I2C/nose/Nose_Board_Manager.h"

static Eye_Board_Manager eyes;
static Nose_Board_Manager noses;
static Mouth_Board_Manager mouths;

void setup()
{

  noses.setup_I2C_8x8();
  eyes.setup_I2C_8x16();
  mouths.setup_SPI_32x4();
}

void loop()
{
  noses.main_I2C_8x8();
  eyes.main_I2C_8x16();
  mouths.main_SPI_32x4();
}
