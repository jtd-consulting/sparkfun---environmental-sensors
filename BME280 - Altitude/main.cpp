#include "BME280.h"
#include "mbed.h"
#include <cmath>
#include <iterator>

// create BME280 object
BME280 test_sensor(I2C_SDA, I2C_SCL);
// int numberOfDataPoints = 75;

// temperature reading from BME280
float temp_reading;
// pressure reading from BME280
float pressure_reading;

// constants
float gravity = 9.80665;
float universal_gas_constant = 8.3144598;
float molar_mass_air = 0.0289644;

// height of reference level b (m)
float height_0 = 0;
float height_1 = 11000;
float height_2 = 20000;
float height_3 = 32000;
float height_4 = 47000;
float height_5 = 51000;
float height_6 = 71000;
// reference pressure (Pa)
float pressure_0 = 101325;
float pressure_1 = 22632.1;
float pressure_2 = 5474.89;
float pressure_3 = 868.02;
float pressure_4 = 110.91;
float pressure_5 = 66.94;
float pressure_6 = 3.96;
// reference temperature (K)
float temperature_0 = 288.15;
float temperature_1 = 216.65;
float temperature_2 = 216.65;
float temperature_3 = 228.65;
float temperature_4 = 270.65;
float temperature_5 = 270.65;
float temperature_6 = 214.65;
// temperature lapse rate (K/m)
float lapse_rate_0 = -0.0065;
float lapse_rate_2 = 0.001;
float lapse_rate_3 = 0.0028;
float lapse_rate_5 = -0.0028;
float lapse_rate_6 = -0.002;

float exponent_0 =
    (gravity * molar_mass_air) / (universal_gas_constant * lapse_rate_0);
float exponent_2 =
    (gravity * molar_mass_air) / (universal_gas_constant * lapse_rate_2);
float exponent_3 =
    (gravity * molar_mass_air) / (universal_gas_constant * lapse_rate_3);
float exponent_5 =
    (gravity * molar_mass_air) / (universal_gas_constant * lapse_rate_5);
float exponent_6 =
    (gravity * molar_mass_air) / (universal_gas_constant * lapse_rate_6);

// pressure in hPa
void printAltitude(float pressure_hpa) {

  // hectopascal to pascal
  float pressure = pressure_hpa * 100;

  // b = 0 (lapse rate is not zero)
  float altitude_0 = (((temperature_0 / (pow((pressure / pressure_0), 1 / exponent_0))) - temperature_0) / lapse_rate_0) + height_0;
  // printf("b = 0: %f metres\n", altitude_0);
  
  // b = 1 (lapse rate is zero)
  float altitude_1 = ((-log(pressure/pressure_1) * universal_gas_constant * temperature_1) / (gravity * molar_mass_air)) + height_1;
  // printf("b = 1: %f metres\n", altitude_1);
  
  // b = 2 (lapse rate is not zero)
  float altitude_2 = (((temperature_2 / (pow((pressure / pressure_2), 1 / exponent_2))) - temperature_2) / lapse_rate_2) + height_2;
  // printf("b = 2: %f metres\n", altitude_2);

  // b = 3 (lapse rate is not zero)
  float altitude_3 = (((temperature_3 / (pow((pressure / pressure_3), 1 / exponent_3))) - temperature_3) / lapse_rate_3) + height_3;
  // printf("b = 3: %f metres\n", altitude_3);

  // b = 4 (lapse rate is zero)
  float altitude_4 = ((-log(pressure/pressure_4) * universal_gas_constant * temperature_4) / (gravity * molar_mass_air)) + height_4;
  // printf("b = 4: %f metres\n", altitude_4);
  
  // b = 5 (lapse rate is not zero)
  float altitude_5 = (((temperature_5 / (pow((pressure / pressure_5), 1 / exponent_5))) - temperature_5) / lapse_rate_5) + height_5;
  // printf("b = 5: %f metres\n", altitude_5);

  // b = 6 (lapse rate is not zero)
  float altitude_6 = (((temperature_6 / (pow((pressure / pressure_6), 1 / exponent_6))) - temperature_6) / lapse_rate_6) + height_6;
  // printf("b = 6: %f metres\n", altitude_6);

  printf("\n");

    // pressure at sea level: 101325.00 Pa
    // temperature: 15 degrees Celsius
    // values calculated here: https://keisan.casio.com/exec/system/1224579725
  if (pressure <= 101325.00 && pressure > 31599) {
      // b = 0 (0 to 11000 m)
      printf("b = 0: %f metres\n", altitude_0);
  } else if (pressure <= 31599 && pressure > 14308) {
      // b = 1 (11000 to 20000 m)
      printf("b = 1: %f metres\n", altitude_1);
  } else if (pressure <= 14308 && pressure > 5822) {
      // b = 2 (20000 to 32000 m)
      printf("b = 2: %f metres\n", altitude_2);
  } else if (pressure <= 5822 && pressure > 2267) {
      // b = 3 (32000 to 47000 m)
      printf("b = 3: %f metres\n", altitude_3);
  } else if (pressure <= 2267 && pressure > 1810) {
      // b = 4 (47000 to 51000 m)
      printf("b = 4: %f metres\n", altitude_4);
  } else if (pressure <= 1810 && pressure > 665) {
      // b = 5 (51000 to 71000 m)
      printf("b = 5: %f metres\n", altitude_5);
  } else if (pressure <= 665) {
      // b = 6 (above 71000 m)
      printf("b = 6: %f metres\n", altitude_6);
  }
}

int main() {
  test_sensor.initialize();

  // wait 2 seconds
  wait_us(2000000);

  printf("///////////////////START///////////////////\n");

  while (true) {
    // wait 2 seconds
    wait_us(2000000);

    // read from sensor
    temp_reading = test_sensor.getTemperature();
    pressure_reading = test_sensor.getPressure();

    printAltitude(pressure_reading);
  }
}
