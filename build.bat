@echo off

REM Clone vcpkg if it doesn't exist
IF NOT EXIST "vcpkg" (
    git clone https://github.com/microsoft/vcpkg.git
    call vcpkg\bootstrap-vcpkg.bat
)

REM Set the vcpkg root directory
for /f "delims=" %%i in ('cd') do set "VCPKG_ROOT=%%i\vcpkg"

REM --- 64-bit Build ---


REM Install dependencies
call %VCPKG_ROOT%\vcpkg install

cmake --fresh -S . -B build64 -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake 

REM Build the project
cmake --build build64


REM --- 32-bit Build ---


REM Install dependencies for 32-bit
call %VCPKG_ROOT%\vcpkg install --triplet x86-windows

REM Build the project for 32-bit
cmake --fresh -S . -B build32  -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake -DCMAKE_GENERATOR_PLATFORM=x86 
cmake --build build32