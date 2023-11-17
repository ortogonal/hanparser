cmake_minimum_required(VERSION 3.5)

project(HanService)

enable_testing()

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(src)
add_subdirectory(test)
