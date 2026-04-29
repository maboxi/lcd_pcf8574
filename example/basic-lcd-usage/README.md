# Basic LCD Usage

This example shows how to use the LCD driver with the STM32F401CCU6 using I2C1 and the STM32CubeF4 HAL.

## Build

Configure the example with a toolchain file and let CMake fetch the HAL sources through CPM.

```bash
cmake -S example/basic-lcd-usage -B example/basic-lcd-usage/build \
  -DCMAKE_TOOLCHAIN_FILE=example/basic-lcd-usage/cmake/arm-none-eabi-gcc.cmake
cmake --build example/basic-lcd-usage/build
```

## Wiring

The example uses I2C1 on PB8/PB9 by default. Adjust the pin assignment in `src/stm32f4xx_hal_msp.c` if your board wiring differs.
