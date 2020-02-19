cmake_minimum_required(VERSION 3.5)

set(target "ApplicationServerODataPlugin")
project(${target} LANGUAGES CXX)

add_definitions(-DODATASERVER_LIBRARY)
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
if(WIN32)
set(ApplicationServer_DIR "C:/Program Files (x86)/ApplicationServer/bin")
else()
set(ApplicationServer_DIR "/user/bin/")
endif()
find_package(Qt5Core REQUIRED)
find_package(Qt5HttpServer REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(ApplicationServer)
find_package(ODataServer)
qt5_use_modules(${target} Core HttpServer Xml)
target_include_directories(${target} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)    
target_link_libraries(${target} ApplicationServerCore ApplicationServerInterface ODataServer)
install(TARGETS ${target} DESTINATION "${ApplicationServer_DIR}/plugins")
install(FILES ${HEADER} DESTINATION "${ApplicationServer_DIR}/../include")