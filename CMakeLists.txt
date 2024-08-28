cmake_minimum_required(VERSION 3.16) 

project(adbLib) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compiler flags
set(CMAKE_CXX_FLAGS "-g -Wall ")


set(OSBitness 32)
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

message(STATUS ">>>>>>>>  OS : ${CMAKE_HOST_SYSTEM_NAME}_${OSBitness}  <<<<<<<<")

set(CMAKE_BUILD_RPATH "$ORIGIN/lib") #dynamic lib search for binary in lib dir

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Set the output directory for product
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/${CMAKE_SYSTEM_NAME}_${OSBitness})

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)

include_directories(${Boost_INCLUDE_DIRS})

include_directories( ${CMAKE_SOURCE_DIR}/include)

file(GLOB LIB_SRC ${CMAKE_SOURCE_DIR}/lib/*.cpp)

file(GLOB INCD_SRC ${CMAKE_SOURCE_DIR}/include/*.hpp)

if(MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON )
endif()
#####################################################################
##############   adbLib build   #################################


# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system thread asio)


add_library(${PROJECT_NAME} SHARED ${LIB_SRC} ${INCD_SRC})


# Link Boost libraries
target_link_libraries( ${PROJECT_NAME} PRIVATE Boost::system Boost::thread Boost::asio)


#####################################################################
##############   exampleUse build   #################################

file(GLOB BIN_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp )

# Add your source files
add_executable( exampleUse ${BIN_SRC} ${INCD_SRC})


target_link_libraries(exampleUse PRIVATE ${PROJECT_NAME})

#####################################################################

