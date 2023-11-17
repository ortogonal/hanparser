cmake_minimum_required(VERSION 3.5)

project(hanreader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    datatype.h
    hanparser.h
)

set(SOURCES
    datatype.cpp
    hanparser.cpp
    main.cpp
)

add_executable(hanreader ${HEADERS} ${SOURCES})

include(GNUInstallDirs)
install(TARGETS hanreader
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
