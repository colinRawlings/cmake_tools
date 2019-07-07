project(LibPCH)

message(STATUS "Processing: lib_pch")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib_pch)

target_sources(lib_pch
               PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.h # the pch
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.cpp # the placeholder
                                                              # cpp for the pch
               ${CMAKE_CURRENT_SOURCE_DIR}/include/pch_lib.h # the lib header
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_lib.cpp # the user of the pch
               )

target_include_directories(lib_pch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_command(
  TARGET lib_pch POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:lib_pch>
          ${BINARY_OUTDIR}/$<CONFIG>)

#
# configure pch behaviour
#

# configure variables

set(pch_header_filepath ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.h)
set(pch_placeholder_filepath ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.cpp)

get_filename_component(pch_header_filename ${pch_header_filepath} NAME)
get_filename_component(pch_base_name ${pch_header_filepath} NAME_WE)

set(pch_binary_filepath "${CMAKE_CFG_INTDIR}/${pch_base_name}.pch")

#

message(STATUS "pch_header_filepath: ${pch_header_filepath}")
message(STATUS "pch_placeholder_filepath: ${pch_placeholder_filepath}")

message(STATUS "pch_header_filename: ${pch_header_filename}")
message(STATUS "pch_base_name: ${pch_base_name}")

message(STATUS "pch_binary_filepath: ${pch_binary_filepath}")

# pch binary

set_source_files_properties(
  ${pch_placeholder_filepath}
  PROPERTIES
  COMPILE_FLAGS
  "/Yc\"${pch_header_filename}\" /Fp\"${pch_binary_filepath}\""
  OBJECT_OUTPUTS
  "${pch_binary_filepath}")

# consumers of pch binary(/pch header): only lib_pch.cpp

set_source_files_properties(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_lib.cpp
  PROPERTIES
  COMPILE_FLAGS
  "/Yu\"${pch_header_filename}\" /Fp\"${pch_binary_filepath}\" /FI\"${pch_header_filename}\""
  # "/Yu\"${pch_header_filename}\" /Fp\"${pch_binary_filepath}\"" # with this
  # line the pch must be explicitly added to the consuming cpp
  OBJECT_DEPENDS "${pch_binary_filepath}")
