/* Main Program */

void setup() {
  setup_SPI_32x4();
  setup_I2C_8x8();
}

void loop() {
  main_SPI_32x4();
  main_I2C_8x8();
}