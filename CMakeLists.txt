cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
find_package(fitsio REQUIRED)
find_package(UnitTest++ REQUIRED)

set(SRCS 
    ${CMAKE_SOURCE_DIR}/FitsObject.cpp
    ${CMAKE_SOURCE_DIR}/Test.cpp
    )

set(HDRS
    ${CMAKE_SOURCE_DIR}/FitsObject.h
    )

include_directories(
    ${UNITTESTPP_INCLUDE_DIR}
    ${FITSIO_INCLUDE_DIR}
    )

add_executable(FitsObjectTest ${SRCS} ${HDRS})

target_link_libraries(
    FitsObjectTest
    ${FITSIO_LIBRARIES}
    ${UNITTESTPP_LIBRARIES}
    )
