cmake_minimum_required(VERSION 3.13)

# /usr/share/cmake-3.16/Modules/FindPkgConfig.cmake
# set(PKG_CONFIG_EXECUTABLE "$ENV{PKG_CONFIG}" CACHE FILEPATH "pkg-config executable")
# mark_as_advanced(PKG_CONFIG_EXECUTABLE)
find_package(PkgConfig)
pkg_search_module(xorg-server REQUIRED xorg-server IMPORTED_TARGET GLOBAL)

pkg_search_module(x11 REQUIRED x11 IMPORTED_TARGET GLOBAL)


set(CMAKE_DEBUG_TARGET_PROPERTIES
  #INCLUDE_DIRECTORIES
  # COMPILE_DEFINITIONS
  COMPILE_OPTIONS
  AUTOUIC_OPTIONS
  POSITION_INDEPENDENT_CODE
  )

set(sources
  fork-to.c
  )

add_executable(forkto ${sources})

# local dependency:
target_link_libraries(forkto libfork)
target_include_directories(forkto PRIVATE ../include/)

# any better way?
target_link_libraries(forkto ${x11_LINK_LIBRARIES})
target_include_directories(forkto SYSTEM PUBLIC ${x11_INCLUDE_DIRS})

target_include_directories(forkto SYSTEM PUBLIC ${xorg-server_INCLUDE_DIRS})

install(TARGETS forkto DESTINATION /usr/bin )
