cmake_minimum_required(VERSION 3.5)

set(target "ApplicationServerODataPlugin")
project(${target} LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC
    "*.cpp"
)
file(GLOB HEADER
    "*.h"
    "*.hpp"
)
add_library(${target} SHARED ${SRC})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5HttpServer REQUIRED)
qt5_use_modules(${target} Core HttpServer)
target_include_directories(${target} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)    
target_link_libraries(${target} ApplicationServerCore ApplicationServerInterface)