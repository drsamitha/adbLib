cmake_minimum_required(VERSION 3.8) 

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


# Set the output directory for product
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/${CMAKE_SYSTEM_NAME}_${OSBitness})

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)


include_directories( ${CMAKE_SOURCE_DIR}/include)

file(GLOB LIB_SRC ${CMAKE_SOURCE_DIR}/lib/*.cpp)

file(GLOB INCD_SRC ${CMAKE_SOURCE_DIR}/include/*.hpp)

#####################################################################
##############   adbLib build   #################################


# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system thread)


add_library(${PROJECT_NAME} SHARED ${LIB_SRC} ${INCD_SRC})


# Link Boost libraries
target_link_libraries( ${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})


#####################################################################
##############   exampleUse build   #################################

file(GLOB BIN_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp )

# Add your source files
add_executable( exampleUse ${BIN_SRC} ${INCD_SRC})


target_link_libraries(exampleUse PRIVATE ${PROJECT_NAME})

#####################################################################

