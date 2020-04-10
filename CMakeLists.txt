cmake_minimum_required(VERSION 2.8)

project(iocolors)

set(CMAKE_CXX_FLAGS "-Wall -m64 -O3 " )

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)