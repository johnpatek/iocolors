cmake_minimum_required(VERSION 2.8)

project(iocolors)

set(CMAKE_CXX_FLAGS "-Wall -Werrow -Wextra -Wpedantic -O3" )

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(DOCS)
    find_package(Doxygen)
    add_subdirectory(docs)
endif()

add_subdirectory(src)