<<<<<<< HEAD
# Copyright Benoit Blanchon 2014-2016
# MIT License
# 
# Arduino JSON library
# https://github.com/bblanchon/ArduinoJson
=======
# Copyright Benoit Blanchon 2014-2017
# MIT License
# 
# Arduino JSON library
# https://bblanchon.github.io/ArduinoJson/
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
# If you like this project, please add a star!

cmake_minimum_required(VERSION 3.0)
project(ArduinoJson)

enable_testing()

<<<<<<< HEAD
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

=======
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
if(${COVERAGE})
	set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

<<<<<<< HEAD
=======
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
add_subdirectory(third-party/catch)
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
add_subdirectory(test)
