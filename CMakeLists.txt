cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)

#

project(test_cmake_tools)

# top level options

option(BUILD_SHARED_LIBS "build shared libs" ON)

option(USE_CLCACHE "configure for use with clcache (/Z7 instead of /Zi)" ON)
#[[
For smoothest integration place move cl.exe and its config to -> cl_original.exe
Then copy the clcache.exe to the former location of cl.exe.  In this way the
cmake-tools still finds the crt paths.
#]]

option(USE_LIB_A "use lib a" ON)
option(USE_LIB_C "use lib c" OFF)

message(STATUS "Configuring: ")
message(STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS})
message(STATUS "USE_LIB_A: " ${USE_LIB_A})
message(STATUS "USE_LIB_C: " ${USE_LIB_C})

#

set(BINARY_OUTDIR ${PROJECT_BINARY_DIR}/bin)
message(STATUS "BINARY_OUTDIR: ${BINARY_OUTDIR}")

# compiler settings

if (${USE_CLCACHE})
  set(debug_info_flag "/Z7")
else()
  set(debug_info_flag "/Zi")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "/MDd ${debug_info_flag} /Ob0 /Od /RTC1")

# boost

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)

set(Boost_DEBUG OFF)

#[[
For vscode define BOOST_DIR with:
"cmake.configureSettings": {
  "BOOST_DIR": "<path_to_boost>\\boost_1_70_0",
},
#]]

if(NOT DEFINED BOOST_DIR)
  message(
    FATAL_ERROR
      "BOOST_DIR must be defined, do so with CMAKE_GUI or .vscode/settings.json: \n\"cmake.configureSettings\": {\"BOOST_DIR\": \"<path_to_boost>\\boost_1_70_0\"}\""
    )
endif()

set(BOOST_INCLUDEDIR ${BOOST_DIR})
set(BOOST_LIBRARYDIR ${BOOST_DIR}/stage/lib)

#

if(USE_LIB_A)
  add_subdirectory(lib_a)
endif(USE_LIB_A)

# add_subdirectory(lib_b)

if(USE_LIB_C)
  add_subdirectory(lib_c)
endif(USE_LIB_C)

add_subdirectory(lib_pch)

# library consumers

add_subdirectory(app)
# add_subdirectory(test_runner)
