cmake_minimum_required(VERSION 3.5)

project("ApplicationServerODataPluginTests" LANGUAGES CXX)

enable_testing()
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  add_executable(ApplicationServerODataPluginTests ${SRC})
find_package(Qt5Core REQUIRED)
qt5_use_modules(ApplicationServerODataPluginTests Core Test)

add_test(ApplicationServerODataPluginTests ${CMAKE_BINARY_DIR}/bin/ApplicationServerODataPluginTests)
    set_property(TEST ApplicationServerODataPluginTests PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CMAKE_BINARY_DIR}/bin:${CMAKE_BINARY_DIR}/lib")
target_link_libraries(ApplicationServerODataPluginTests ApplicationServerCore ApplicationServerInterface ApplicationServerODataPlugin)