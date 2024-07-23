@echo off

REM Clone vcpkg if it doesn't exist
IF NOT EXIST "vcpkg" (
    git clone https://github.com/microsoft/vcpkg.git
    call vcpkg\bootstrap-vcpkg.bat
)

REM Set the vcpkg root directory
for /f "delims=" %%i in ('cd') do set "VCPKG_ROOT=%%i\vcpkg"

REM Install dependencies
call %VCPKG_ROOT%\vcpkg install

REM Create and navigate to the build directory
IF EXIST "build" rd /s /q "build"
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake ..

REM Build the project
cmake --build .