#include "CCS811.h"
#include "mbed.h"
#include <cstdint>

// determines how long sensor records data
#define number_of_data_points 31

// create CCS811 object
CCS811 test_sensor(I2C_SDA, I2C_SCL);

// unsigned 16-bit integers
uint16_t eco2, tvoc;

// CCS811 readings
int eco2_max, tvoc_max;

int main() {
  // initialize CCS811
  test_sensor.init();
  test_sensor.readData(&eco2, &tvoc);

  printf("///////////////////START///////////////////\n");
  // wait 2 seconds
  wait_us(2000000);
  // prompt user
  printf("Prepare to blow in 3 seconds:\n");
  // wait 0.5 seconds
  wait_us(500000);
  // provide countdown for user
  printf("3\n");
  wait_us(1000000); // wait 1 second
  printf("2\n");
  wait_us(1000000); // wait 1 second
  printf("1\n");
  wait_us(1000000); // wait 1 second
  printf("BLOW\n");
  wait_us(250000); // wait 0.25 seconds

  // keeps track of CO2 and TVOC values while user blows
  for (int i = 0; i < number_of_data_points; i++) {
    test_sensor.readData(&eco2, &tvoc);
    
    // print sensor readings
    printf("[%u]ppm, [%u]ppb, %d\n", eco2, tvoc, i);
    
    // store the first data points
    if (i == 0) {
      eco2_max = eco2;
      tvoc_max = tvoc;
    }
    // update max values for CO2 and TVOC
    if (eco2_max < eco2) {
      eco2_max = eco2;
    }
    if (tvoc_max < tvoc) {
      tvoc_max = tvoc;
    }
    // wait 0.1 seconds
    wait_us(100000);
  }

  // print max values
  printf("eco2_max is: %d\n", eco2_max);
  printf("tvoc_max is: %d\n", tvoc_max);

  // determine if user was wearking a mask or not (using max CO2 and TVOC values)
  if (eco2_max >= 400 && eco2_max < 430) {
    // face shield, N95, or did not blow
    printf("user wearing face shield/N95 or did not blow\n");
  } else if (eco2_max >= 430 && eco2_max < 1400) {
    // thinner masks
    printf("wearing mask\n");
  } else {
    // not wearing mask or blowing very hard through thin mask
    printf("not wearing mask\n");
  }
}
