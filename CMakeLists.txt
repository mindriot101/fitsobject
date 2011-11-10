cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
find_package(fitsio REQUIRED)
find_package(UnitTest++ REQUIRED)

set(SRCS 
    ${CMAKE_SOURCE_DIR}/FitsObject.cpp
    )

set(HDRS
    ${CMAKE_SOURCE_DIR}/FitsObject.h
    )

include_directories(
    ${UNITTESTPP_INCLUDE_DIR}
    ${FITSIO_INCLUDE_DIR}
    )

add_library(FitsObject ${SRCS} ${HDRS})

target_link_libraries(
    FitsObject
    ${FITSIO_LIBRARIES}
    )

set(RESULTLIB ${CMAKE_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}FitsObject${CMAKE_STATIC_LIBRARY_SUFFIX})

add_executable(FitsObjectTest ${CMAKE_SOURCE_DIR}/Test.cpp)
target_link_libraries(FitsObjectTest
    ${RESULTLIB}
    ${UNITTESTPP_LIBRARIES}
    ${FITSIO_LIBRARIES}
    )
