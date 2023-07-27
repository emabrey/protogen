/* Main Program */

#include "src/SPI/mouth/SPI_Mouth_Board.h"
#include "src/I2C/eye/I2C_Eye_Board.h"
#include "src/I2C/nose/I2C_Nose_Board.h"

void setup()
{
  setup_SPI_32x4();
  setup_I2C_8x8();
  setup_I2C_16x8();
}

void loop()
{
  main_SPI_32x4();
  main_I2C_8x8();
  main_I2C_16x8();
}
