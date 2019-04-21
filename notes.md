# Configuring vs code
- Useful extensions:
    - cmake-tools
    - GitLens

# Configuring cmake-tools

- By default `cmake-tools` seems to select `Ninja` as the generator. To override add the settings `<path to project>/.vscode/settings.json`:
    ```json
    "C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",
    
    "cmake.generator" : "Visual Studio 15 2017 Win64",
    "cmake.configureOnOpen": false,
    ```
  (of course only the second setting is directly relevant to forcing the generator).

# Configure CMake project

## bool options

- Define: 
    ```cmake
    option(USE_LIB_A "use lib a" OFF)
    ```

- Use:
    ```cmake
    if(USE_LIB_A)
        add_subdirectory(lib_a)
    endif(USE_LIB_A)
    ```

## Defining dropdown options

- Define: 
    ```cmake
    set(c_sub_lib_name "one" CACHE STRING "sub lib used by lib c")
    set_property(CACHE c_sub_lib_name
                PROPERTY STRINGS ${LIB_ONE_NAME} ${LIB_TWO_NAME})
    ```

- Use:
    ```cmake
    if(${c_sub_lib_name} STREQUAL ${LIB_ONE_NAME})
        message(STATUS "Using lib one")
        add_subdirectory(sub_lib_one)
    elseif(${c_sub_lib_name} STREQUAL ${LIB_TWO_NAME})
        message(STATUS "Using lib two")
        add_subdirectory(sub_lib_two)
    else()
        message(STATUS "No lib found")
    endif(${c_sub_lib_name} STREQUAL ${LIB_ONE_NAME})
    ```

# Configuring the CPP project

## lib/app skeleton




