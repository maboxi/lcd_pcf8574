# Embedded Development DevContainer

This devcontainer is configured for embedded C/C++ development with support for STM32 microcontrollers and other embedded boards.

## Included Tools & Extensions

### VS Code Extensions
- **C/C++ Development Extension Pack** - Complete C/C++ development environment
- **CMake Tools** - Integrated CMake support
- **C/C++ Tools** - IntelliSense, debugging, and code browsing
- **CMake** - Syntax highlighting and language support

### System Tools
- **CMake** - Build system generator
- **GCC/G++** - C and C++ compilers
- **ARM GCC toolchain** - `arm-none-eabi-gcc`, `binutils-arm-none-eabi`, and `libnewlib-arm-none-eabi`
- **Ninja** - Fast incremental build backend
- **GDB** - GNU Debugger
- **OpenOCD** - Debugging and flashing for ARM microcontrollers
- **stlink-tools** - ST-Link command-line utilities for probing and flashing STM32 devices
- **libftdi** - FTDI USB driver library
- **libusb** - USB device library
- **libhidapi** - USB HID device library

## USB Device Support

The devcontainer is configured to mount and access USB devices, particularly:
- **ST-Link v2** and **ST-Link v3** debuggers (for STM32)
- Other USB-based programmers and debuggers

### Udev Rules
Udev rules for ST-Link are automatically installed in `/etc/udev/rules.d/99-stlink.rules`.

### Running Commands

```bash
# Flash firmware to device via OpenOCD
openocd -f board/stm32f4discovery.cfg -c "program build/firmware.elf verify reset exit"

# Probe an attached ST-Link and target MCU
st-info --probe

# Debug with GDB
arm-none-eabi-gdb build/firmware.elf
```

## Building Your Project

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make -j$(nproc)
```

## Notes

- The container runs as `root` to allow USB device access
- `--privileged` and device cgroup rules are enabled for hardware access
- `/dev/bus/usb` is mounted into the container for USB device visibility
