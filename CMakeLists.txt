set(target "ApplicationServerODataPlugin")
if(NOT CMAKE_PROJECT_NAME)
project(${target} LANGUAGES CXX)
endif()

add_definitions(-DODATASERVER_LIBRARY)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
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
find_package(Qt5Xml REQUIRED)
if(${PACKAGE})
find_package(ApplicationServer)
find_package(ODataServer)
endif()
qt5_use_modules(${target} Core HttpServer Xml)
target_include_directories(${target} PUBLIC 
 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_FOLDER}>
)    
target_precompile_headers(${target}
 PUBLIC
  "ApplicationServerODataPlugin.Precompiled.h"
 )
target_link_libraries(${target} ApplicationServerCore ApplicationServerInterface ODataServer)
install(TARGETS ${target} EXPORT ${target} 
LIBRARY DESTINATION "${LIB_FOLDER}"
    ARCHIVE DESTINATION "${LIB_FOLDER}"
    RUNTIME DESTINATION "${PLUGIN_FOLDER}"
    INCLUDES DESTINATION "${INCLUDE_FOLDER}")
install(
  EXPORT ${target} 
  DESTINATION ${LIB_FOLDER}
  )
install(FILES ${HEADER} DESTINATION ${INCLUDE_FOLDER})
