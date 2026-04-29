#!/bin/bash
set -e

# Update package lists
apt-get update

# Install build tools and development utilities
apt-get install -y \
    build-essential \
    cmake \
    gcc \
    g++ \
    gdb \
    gdb-multiarch \
    ninja-build \
    usbutils \
    make \
    pkg-config \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi

# Install OpenOCD and USB support libraries
apt-get install -y \
    openocd \
    stlink-tools \
    libftdi1 \
    libftdi1-dev \
    libusb-1.0-0 \
    libusb-1.0-0-dev \
    libhidapi-dev \
    libx11-6 \
    libxext6 \
    libxrender1 \
    libxtst6 \
    libxi6

# Create OpenOCD scripts directory
mkdir -p /etc/openocd

echo "Setup complete!"
