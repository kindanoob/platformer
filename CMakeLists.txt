cmake_minimum_required(VERSION 3.0)

project(platformer)

file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE RESOURCES resources/fonts/* resources/textures/*)

set(EXECUTABLE_NAME "platformer")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${RESOURCES})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=c++11 -Wall -g -O3)

file(COPY ${RESOURCES} DESTINATION resources/fonts)
file(COPY ${RESOURCES} DESTINATION resources/textures)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.3.2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

