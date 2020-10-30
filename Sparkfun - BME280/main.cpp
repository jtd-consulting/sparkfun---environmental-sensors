#include "BME280.h"
#include "mbed.h"

// create BME280 object
BME280 test_sensor(I2C_SDA, I2C_SCL);

int main() {
  test_sensor.initialize();

  // wait 2 seconds
  wait_us(2000000);

  printf("///////////////////START///////////////////\n");

  while (true) {
    // wait 0.75 seconds
    wait_us(750000);
    // print values as integers
    printf("Temp: [%2.2d]C, Pressure: [%04.2d]hPa, Humidity: [%2.2d]%%\n",
           (int)test_sensor.getTemperature(), (int)test_sensor.getPressure(),
           (int)test_sensor.getHumidity());
           
  }
}
