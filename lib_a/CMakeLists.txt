project(LibA)

message(STATUS "Processing lib_a")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "BOOST_LIBRARYDIR: " ${BOOST_LIBRARYDIR})

find_package(Boost COMPONENTS filesystem REQUIRED)

add_library(lib_a)

target_sources(lib_a
               PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/a_lib.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/include/a_lib.h)

message(STATUS "Boost_FOUND: " ${Boost_FOUND})
message(STATUS "Boost_LIBRARIES: " ${Boost_LIBRARIES})
message(STATUS "Boost_INCLUDE_DIRS: " ${Boost_INCLUDE_DIRS})

target_compile_definitions(lib_a PUBLIC BOOST_ALL_DYN_LINK)

# target_link_libraries(lib_a BOOST::system) ??? Why doesn't this work
target_link_libraries(lib_a ${Boost_LIBRARIES})
target_include_directories(lib_a PRIVATE ${Boost_INCLUDE_DIRS})

target_include_directories(lib_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_command(TARGET lib_a POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${BOOST_LIBRARYDIR} ${BINARY_OUTDIR})

add_custom_command(TARGET lib_a POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           $<TARGET_FILE_DIR:lib_a> ${BINARY_OUTDIR})

# tests

add_subdirectory(tests)
