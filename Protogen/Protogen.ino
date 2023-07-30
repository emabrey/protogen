/* Main Program */
#include "src/renderers/Eye_Renderer.h"
#include "src/renderers/Nose_Renderer.h"
#include "src/renderers/Mouth_Renderer.h"

static Eye_Renderer eyes;
static Nose_Renderer noses;
static Mouth_Renderer mouths;

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
