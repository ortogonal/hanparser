cmake_minimum_required(VERSION 3.5)

project(hanreader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalAntlr4Cpp)
include(FindANTLR)

find_package(ANTLR REQUIRED)

antlr_target(HanProtoParser hanproto.g4 VISITOR PACKAGE hp)

set(HEADERS
    datatype.h
    hanparser.h
)

set(SOURCES
    ${ANTLR_HanProtoParser_CXX_OUTPUTS}

    datatype.cpp
    hanparser.cpp
    main.cpp
)

add_executable(hanreader ${HEADERS} ${SOURCES})
target_include_directories(hanreader
    PUBLIC /usr/include/antlr4-runtime
    PUBLIC ${ANTLR_HanProtoParser_OUTPUT_DIR}
)
target_link_libraries(hanreader PUBLIC antlr4-runtime)

include(GNUInstallDirs)
install(TARGETS hanreader
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
