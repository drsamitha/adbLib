#!/bin/bash

# Clone vcpkg if it doesn't exist
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/microsoft/vcpkg.git
    ./vcpkg/bootstrap-vcpkg.sh
fi

# Set the vcpkg root directory
VCPKG_ROOT=$(realpath ./vcpkg)

# Install dependencies
${VCPKG_ROOT}/vcpkg install

# Create and navigate to the build directory
cmake --fresh -S . -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake 

# Build the project
cmake --build build
