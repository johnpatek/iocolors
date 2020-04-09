file(GLOB IOCOLORS_SOURCES
    "include/*.h"    
    "*.c"
)

include_directories(include)

add_library(iocolors STATIC ${IOCOLORS_SOURCES})

target_include_directories(iocolors PUBLIC include)

install(TARGETS iocolors
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(DIRECTORY include/ 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        PATTERN "include/*.h")