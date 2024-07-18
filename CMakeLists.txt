cmake_minimum_required(VERSION 3.28)
project(cgal_tutorial)

set(CMAKE_CXX_STANDARD 20)

set(CGAL_TUTORIAL_SRC_DIR "${CMAKE_SOURCE_DIR}/src")

###############################################################################
# Package - boost                                                             #
###############################################################################
find_package(Boost 1.85 REQUIRED)

###############################################################################
# Package - cgal                                                              #
###############################################################################
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE ON)
find_package(CGAL REQUIRED)

add_subdirectory(${CGAL_TUTORIAL_SRC_DIR})

