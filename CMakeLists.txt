cmake_minimum_required(VERSION 2.8)

project(iocolors)
if(WIN32)
    # TODO: figure it out
else()
    set(CMAKE_CXX_FLAGS "-Wall -Werrow -Wextra -Wpedantic -O3" )
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(DOCS)
    find_package(Doxygen)
    add_subdirectory(docs)
endif()

add_subdirectory(src)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

if (WIN32)
    set(PLATFORM "WINDOWS")
    set(PACKAGE "MSI")
elseif (APPLE)
    set(PACKAGE "APPLE")
    set(PLATFORM "APPLE")
    set(GENERATOR "APPLE")
else()
    set(PACKAGE "DEB")
    set(PLATFORM "UBUNTU")
    set(GENERATOR "DEBIAN")
endif()

set(CPACK_PACKAGE_NAME "iocolors")

install(
  DIRECTORY ${CMAKE_INSTALL_PREFIX}/
  DESTINATION .
  COMPONENT dev
  USE_SOURCE_PERMISSIONS
  FILES_MATCHING
  PATTERN *.h
  PATTERN *.a
  PATTERN home EXCLUDE
  PATTERN share EXCLUDE
  PATTERN bin EXCLUDE
  PATTERN pkgconfig EXCLUDE
  PATTERN cmake EXCLUDE)

set(CPACK_${PACKAGE}_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL dev)

set(CPACK_GENERATOR ${PACKAGE})

if(WIN32)
    set(CPACK_PACKAGING_INSTALL_PREFIX "C:/Program Files/iocolors")
else()
    set(CPACK_PACKAGING_INSTALL_PREFIX /usr)
endif()

set(CPACK_PACKAGE_CONTACT "John R. Patek <johnpatek2@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION "IOColors development package")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IOColors development package")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_VENDOR "John Patek")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
include (CPack)