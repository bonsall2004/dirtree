cmake_minimum_required(VERSION 3.20)
project(dirtree)

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/windows)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/linux)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/macos)
endif()

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_executable(dirtree ${SOURCES})
target_link_libraries(dirtree PRIVATE CLI11)
target_include_directories(dirtree PRIVATE ../deps/CLI11/include)