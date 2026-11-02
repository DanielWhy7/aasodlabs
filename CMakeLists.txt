cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)

project(cpplabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -Wpedantic -fcontracts")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /W4")
endif()

add_library(lablib STATIC)
target_compile_features(lablib PUBLIC cxx_std_26)
target_sources(lablib
  PRIVATE
    src/tasks.cpp
  PUBLIC FILE_SET "modules" TYPE CXX_MODULES FILES
    src/linked_list.cppm
    src/tasks.cppm
)

add_executable(main)
target_compile_features(main PRIVATE cxx_std_26)
target_sources(main PRIVATE src/main.cpp)
target_link_libraries(main PRIVATE lablib)

add_executable(tests)
target_compile_features(tests PRIVATE cxx_std_26)
target_sources(tests PRIVATE src/test.cpp)
target_link_libraries(tests PRIVATE lablib)
