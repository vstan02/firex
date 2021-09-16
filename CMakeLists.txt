cmake_minimum_required(VERSION 3.20)
project(firex C)

set(CMAKE_C_STANDARD 11)
set(FIREX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FIREX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${FIREX_INCLUDE_DIR})

file(GLOB FIREX_SOURCES "${FIREX_SOURCE_DIR}/*.c")

add_library(firex ${FIREX_SOURCES})

add_executable(demo demo/main.c)
target_link_libraries(demo firex)

install(FILES ${FIREX_INCLUDE_DIR}/firex/*.h DESTINATION include/firex)
install(TARGETS firex ARCHIVE DESTINATION lib)
