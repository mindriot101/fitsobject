cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(TARGET FitsObject)
project(${TARGET})
find_package(fitsio REQUIRED)
find_package(UnitTest++ REQUIRED)

set(TESTFITSFILE "${PROJECT_SOURCE_DIR}/test.fits")

option(ENABLE_SHARED "Compile a shared library (not recommened" OFF)

set(SRCS 
    ${${TARGET}_SOURCE_DIR}/FitsObject.cpp
    )

set(HDRS
    ${${TARGET}_SOURCE_DIR}/FitsObject.h
    )

include_directories(
    ${UNITTESTPP_INCLUDE_DIR}
    /home/astro/phrfbf/build/gcc/include/c++/4.6.2
    /home/astro/phrfbf/build/gcc/include/c++/4.6.2/x86_64-unknown-linux-gnu
    ${FITSIO_INCLUDE_DIR}
    )

if (ENABLE_SHARED)
    add_library(${TARGET} SHARED ${SRCS} ${HDRS})
else(ENABLE_SHARED)
    add_library(${TARGET} ${SRCS} ${HDRS})
endif(ENABLE_SHARED)

target_link_libraries(
    ${TARGET}
    ${FITSIO_LIBRARIES}
    )


# Get the libraries location
get_target_property(RESULTLIB ${TARGET} LOCATION)

add_executable(FitsObjectTest ${${TARGET}_SOURCE_DIR}/Test.cpp)
target_link_libraries(
    FitsObjectTest
    ${RESULTLIB}
    ${UNITTESTPP_LIBRARIES}
    ${FITSIO_LIBRARIES}
    )

add_dependencies(FitsObjectTest ${TARGET})

# Set some nice variables for the parent scope
set(FITSOBJECT_LIBRARIES ${RESULTLIB} PARENT_SCOPE)
set(FITSOBJECT_INCLUDE_DIR ${${TARGET}_SOURCE_DIR} PARENT_SCOPE)
set(FITSOBJECTTARGET ${TARGET} PARENT_SCOPE)
