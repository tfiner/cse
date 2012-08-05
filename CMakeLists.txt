cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(test)

message( STATUS "CMake detected OS '${CMAKE_SYSTEM_NAME}'" )
message( STATUS "Build type - ${CMAKE_BUILD_TYPE}")

SET(BOOST_ROOT "/opt/local")
MESSAGE(STATUS "** Search Boost root: ${BOOST_ROOT}")
# FIND_PACKAGE(Boost COMPONENTS variant REQUIRED)
MESSAGE(STATUS "** Boost Include: ${Boost_INCLUDE_DIR}")
MESSAGE(STATUS "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
MESSAGE(STATUS "** Boost Libraries: ${Boost_LIBRARIES}")

# find_package( Boost REQUIRED COMPONENTS variant)
include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS 
    "-std=c++11 -stdlib=libc++ -DBOOST_TEST_DYN_LINK" )

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DTBB_USE_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")

# Make things easier in the deeper projects.
set(CSE_ROOT /Users/tim/projects/cse)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( SYSTEM ${Boost_INCLUDE_DIR} )

set(SRCS 
    comptest.cpp sys_physics.cpp
)

add_executable(test ${SRCS} )
target_link_libraries( test ${Boost_LIBRARIES} )
