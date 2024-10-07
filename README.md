# WheelTofs

The **`WheelTofs`** class is a C++ library designed to interface with multiple VL53L4CD Time of Flight (ToF) sensors using I2C communication on the STM32 L432KC microcontroller. This library simplifies the initialization, configuration, and distance measurement from these sensors for wheelmodule of the **CRAWLER**.

## Features

- Uses 6 VL53L4CD ToF sensors.
- Configurable distance measurement modes (short and long range).
- Easy-to-use interface for reading distance measurements in millimeters.
- Debugging support to print sensor readings.

## Peripherals

### Microcontroller
- **STM32 L432KC**

### Sensors
- **VL53L4CD/XC Time of Flight Sensors**
  - Supports continuous distance measurement.

### I2C Interface
- **I2C Pins**: Adjust according to your hardware configuration
  - **SDA**: PB_9
  - **SCL**: PB_8

### GPIO Pins for Sensor Control
| Sensor | XSHUT Pin |
|--------|-----------|
| T1     | PA_7     |
| T2     | PA_6     |
| T3     | PA_4     |
| T4     | PA_3     |
| T5     | PA_5     |
| T6     | PA_1     |

## Dependencies

- **Mbed OS**: Ensure that you have Mbed OS installed and configured for your STM32 L432KC development environment.
- **VL53L1X.h Library**: This class requires the VL53L1X.h library for sensor management.

