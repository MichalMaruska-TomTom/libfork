# copied from ../fork-plugin/CMakeLists.txt

cmake_minimum_required(VERSION 3.13)
# https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949

project(libfork LANGUAGES CXX C)

# already set in src/CMakeLists.txt
set(CMAKE_DEBUG_TARGET_PROPERTIES
  INCLUDE_DIRECTORIES COMPILE_DEFINITIONS)

add_compile_options(-fdiagnostics-color=always)

add_subdirectory(lib)
add_subdirectory(src)
