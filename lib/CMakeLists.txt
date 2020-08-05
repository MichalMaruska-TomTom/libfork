cmake_minimum_required(VERSION 3.13)

# /usr/share/cmake-3.13/Modules/FindPkgConfig.cmake
# set(PKG_CONFIG_EXECUTABLE "$ENV{PKG_CONFIG}" CACHE FILEPATH "pkg-config executable")
find_package(PkgConfig)
pkg_search_module(xorg-server REQUIRED xorg-server
  IMPORTED_TARGET GLOBAL)

# fixme: xorg sdk needs this, we don't!
# pkg_search_module(pixman REQUIRED pixman-1 IMPORTED_TARGET GLOBAL)


set(CMAKE_DEBUG_TARGET_PROPERTIES
  #INCLUDE_DIRECTORIES
  # COMPILE_DEFINITIONS
  COMPILE_OPTIONS
  AUTOUIC_OPTIONS
  POSITION_INDEPENDENT_CODE
  )

set(sources fork.c)

add_library(libfork SHARED ${sources})

target_compile_options(libfork PRIVATE "-g")

# set_property(TARGET fork PROPERTY NO_SONAME)
# set_property(TARGET fork PROPERTY OUTPUT_NAME fork.so)

set_target_properties(libfork PROPERTIES PREFIX "")

# /usr/lib/x86_64-linux-gnu/pkgconfig/xorg-server.pc
# or SDK?
target_include_directories(libfork SYSTEM PUBLIC ${xorg-server_INCLUDE_DIRS})
# target_include_directories(libfork SYSTEM PUBLIC ${pixman_INCLUDE_DIRS})

target_include_directories(libfork PUBLIC ../include/)

install(FILES ../include/fork.h
  DESTINATION /usr/include/
  )

install(TARGETS libfork DESTINATION /usr/lib/)
