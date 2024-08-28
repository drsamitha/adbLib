#!/bin/bash

# Clone vcpkg if it doesn't exist
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/microsoft/vcpkg.git
    ./vcpkg/bootstrap-vcpkg.sh
fi

# Set the vcpkg root directory
VCPKG_ROOT=$(realpath ./vcpkg)+"vcpkg"

# Install dependencies
${VCPKG_ROOT}/vcpkg install

# --- 64-bit Build ---

# Create and navigate to the build directory
cmake --fresh -S . -B build64 -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake 

# Build the project
cmake --build build64

# --- 32-bit Build ---

# Install dependencies for 32-bit
${VCPKG_ROOT}/vcpkg install --triplet x86-linux


# Build the project for 32-bit
cmake --fresh -S . -B build32 -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_GENERATOR_PLATFORM=x86 
cmake --build build32


