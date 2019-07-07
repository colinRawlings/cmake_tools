project(LibPCH)

message(STATUS "Processing: lib_pch")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib_pch)

target_sources(lib_pch
               PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.h # the pch
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_header.cpp # the dummy cpp
                                                              # for the pch
               ${CMAKE_CURRENT_SOURCE_DIR}/include/pch_lib.h # the lib header
               ${CMAKE_CURRENT_SOURCE_DIR}/src/pch_lib.cpp # the user of the pch
               )

target_include_directories(lib_pch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_command(TARGET lib_pch POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           $<TARGET_FILE_DIR:lib_pch> ${BINARY_OUTDIR}/$<CONFIG>)