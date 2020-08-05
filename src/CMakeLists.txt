cmake_minimum_required(VERSION 3.13)

# /usr/share/cmake-3.13/Modules/FindPkgConfig.cmake
# set(PKG_CONFIG_EXECUTABLE "$ENV{PKG_CONFIG}" CACHE FILEPATH "pkg-config executable")
# mark_as_advanced(PKG_CONFIG_EXECUTABLE)
find_package(PkgConfig)

set(CMAKE_DEBUG_TARGET_PROPERTIES
  #INCLUDE_DIRECTORIES
  # COMPILE_DEFINITIONS
  COMPILE_OPTIONS
  AUTOUIC_OPTIONS
  POSITION_INDEPENDENT_CODE
  )
# not GLOB_RECURSE
# file(GLOB sources "*.cpp"  "*.c")
set(sources
  fork-to.c
  )

add_executable(forkto ${sources})
