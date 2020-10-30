#include "CCS811.h"
#include "mbed.h"

// create CCS811 object
CCS811 test_sensor(I2C_SDA, I2C_SCL);

// unsigned 16-bit integer
uint16_t eco2, tvoc;

int main() {
  test_sensor.init();

  printf("///////////////////START///////////////////\n");

  // wait 5 seconds
  wait_us(5000000);

  while (true) {
    // test_sensor.readstatus(); //0x90 reports everything working, 0x98

    // measurement ready to be used wait 0.75 seconds
    wait_us(750000);

    test_sensor.readData(&eco2, &tvoc);
    printf("eCO2: [%d]ppm, TVOC: [%d]ppb\n", eco2, tvoc);
  }
}
