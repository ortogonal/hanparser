cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

#include(ExternalAntlr4Cpp)
#include(FindANTLR)
#
#find_package(ANTLR REQUIRED)
#
#antlr_target(HanProtoParserTest ../src/hanproto.g4 VISITOR PACKAGE hp)
#
#
#set (HANPARSER_TEST_SOURCES
#    ${ANTLR_HanProtoParserTest_CXX_OUTPUTS}
#    tst_hanparser.cpp
#    ../src/hanparser.cpp
#)
#
#add_executable(tst_hanparser ${HANPARSER_TEST_SOURCES})
#add_test(NAME tst_hanparser COMMAND tst_hanparser)
#target_include_directories(tst_hanparser
#    PRIVATE ../src
#    PUBLIC /usr/include/antlr4-runtime
#    PUBLIC ${ANTLR_HanProtoParserTest_OUTPUT_DIR}
#)
#target_link_libraries(tst_hanparser
#    PRIVATE gtest gtest_main pthread
#    PUBLIC /usr/include/antlr4-runtime
#    PUBLIC ${ANTLR_HanProtoParserTest_OUTPUT_DIR}
#)

set (DATATYPE_TEST_SOURCES
    tst_datatype.cpp
    ../src/datatype.cpp
)

add_executable(tst_datatype ${DATATYPE_TEST_SOURCES})
add_test(NAME tst_datatype COMMAND tst_datatype)
target_include_directories(tst_datatype PRIVATE ../src)
target_link_libraries(tst_datatype PRIVATE gtest gtest_main pthread)
