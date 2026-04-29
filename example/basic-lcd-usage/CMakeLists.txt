cmake_minimum_required(VERSION 3.21)

project(basic_lcd_usage LANGUAGES C ASM)

set(CPM_DOWNLOAD_VERSION 0.40.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
if(NOT EXISTS "${CPM_DOWNLOAD_LOCATION}")
	file(DOWNLOAD
		https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
		"${CPM_DOWNLOAD_LOCATION}"
		STATUS CPM_DOWNLOAD_STATUS
		TLS_VERIFY ON
	)
	list(GET CPM_DOWNLOAD_STATUS 0 CPM_DOWNLOAD_STATUS_CODE)
	if(NOT CPM_DOWNLOAD_STATUS_CODE EQUAL 0)
		message(FATAL_ERROR "Failed to download CPM.cmake: ${CPM_DOWNLOAD_STATUS}")
	endif()
endif()
include("${CPM_DOWNLOAD_LOCATION}")

CPMAddPackage(
	NAME STM32CubeF4
	GITHUB_REPOSITORY STMicroelectronics/STM32CubeF4
	GIT_TAG v1.28.0
	DOWNLOAD_ONLY YES
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LCD_LIBRARY_TARGET lcd_pcf8574)
add_library(${LCD_LIBRARY_TARGET} STATIC
	${CMAKE_CURRENT_LIST_DIR}/../../src/driver.c
)
target_include_directories(${LCD_LIBRARY_TARGET} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/../../include
)

target_compile_options(${LCD_LIBRARY_TARGET} PRIVATE
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	-ffunction-sections
	-fdata-sections
)

set(HAL_SOURCES
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
)

set(HAL_LIBRARY_TARGET stm32cubef4_hal)
add_library(${HAL_LIBRARY_TARGET} STATIC ${HAL_SOURCES})
target_compile_definitions(${HAL_LIBRARY_TARGET} PUBLIC
	USE_HAL_DRIVER
	STM32F401xC
)
target_include_directories(${HAL_LIBRARY_TARGET} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Include
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_options(${HAL_LIBRARY_TARGET} PRIVATE
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	-ffunction-sections
	-fdata-sections
)

add_executable(${PROJECT_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.c
	${CMAKE_CURRENT_LIST_DIR}/src/stm32f4xx_it.c
	${CMAKE_CURRENT_LIST_DIR}/src/stm32f4xx_hal_msp.c
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xc.s
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	USE_HAL_DRIVER
	STM32F401xC
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/../../include
	${STM32CubeF4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Include
	${STM32CubeF4_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	-ffunction-sections
	-fdata-sections
)

target_link_options(${PROJECT_NAME} PRIVATE
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	-T${CMAKE_CURRENT_LIST_DIR}/STM32F401CCUX_FLASH.ld
	-Wl,--gc-sections
	-Wl,-Map=${PROJECT_NAME}.map
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${LCD_LIBRARY_TARGET}
	${HAL_LIBRARY_TARGET}
)

