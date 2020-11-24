#include "NAU7802.h"
#include "mbed.h"
#include <cstdint>

// link for calculating weight and calibration factor:
// https://learn.sparkfun.com/tutorials/qwiic-scale-hookup-guide?_ga=2.182188711.107793633.1605559681-863993870.1600455968#how-to-characterize-your-scale

// create NAU7802 object
NAU7802 test_sensor(I2C_SDA, I2C_SCL);

// calibration factor for load cell
float calibration_factor;

// used for calibrating load cell (Canadian penny weighs ~2.25 grams)
float calibration_weight(2.25);

// grams
float weight;

// weight in grams of the identical items (i.e. marbles)
float item_weight(5);

// returns weight in grams
float get_weight() {
  weight = (test_sensor.getReading() - test_sensor.getZeroOffset()) /
           test_sensor.getCalibrationFactor();
  return weight;
}

// prints weight in grams
void print_weight() { printf("weight: %f grams\n", get_weight()); }

// print how many of the identical items are being weighed
void print_quantity() { printf("%d marbles in bag\n", (int)get_weight() / 5); }

int main() {
  printf("///////////////////START///////////////////\n");
  // initialize NAU7802
  test_sensor.begin(true);
  // wait 2 seconds
  wait_us(2000000);

  // calculate and store 'zero offset'
  printf("calculating zero offset:\n");
  test_sensor.calculateZeroOffset();
  // wait 0.5 seconds
  wait_us(500000);
  printf("the zero offset is: %d\n", test_sensor.getZeroOffset());
  // wait 0.5 seconds
  wait_us(500000);

  // calibration process
  printf("put on calibration weight\n");
  // wait 7 seconds
  wait_us(7000000);
  // set calibration factor
  calibration_factor =
      (((float)test_sensor.getReading()) - test_sensor.getZeroOffset()) /
      calibration_weight;
  test_sensor.setCalibrationFactor(calibration_factor);
  printf("the calibration factor is: %f\n", test_sensor.getCalibrationFactor());
  // wait 2 seconds
  wait_us(2000000);

  while (true) {
    print_weight();
    print_quantity();
    // wait 1 second
    wait_us(1000000);
  }
}