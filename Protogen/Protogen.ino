/* Main Program */

#include "src/SPI/mouth/Mouth_Board_Manager.h"
#include "src/I2C/eye/Eye_Board_Manager.h"
#include "src/I2C/nose/Nose_Board_Manager.h"

static Eye_Board_Manager eyes;
static Nose_Board_Manager noses;
static Mouth_Board_Manager mouths;

void setup()
{

  noses.setup_I2C();
  eyes.setup_I2C();
  mouths.setup_SPI_32x4();
}

void loop()
{
  noses.main_I2C();
  eyes.main_I2C();
  mouths.main_SPI_32x4();
}
