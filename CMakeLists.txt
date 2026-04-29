project(LCD_PCF8574)
cmake_minimum_required(VERSION 3.8)

set(TARGET LCD_PCF8574)
add_library(${TARGET} src/driver.c)
target_include_directories(${TARGET} PUBLIC include)
