# msvc++ and cmake and vscode

## Configuring `vs code`
- Useful extensions:
    - `C/C++` (by microsoft): intellisense, debugger, code browsing
    - `Python` (by microsoft)
    - `cmake-tools`: include path determination from cmake files, debugger configurations
    - `cmake` (by twxs): syntax highlighting and command completion
    - `cmake format`: auto indentation
    - `GitLens`

- To use `cmder` add the following to `%AppData%\Roaming\Code\User\settings.json` (the file edited when selecting `[File|Preferences|Settings]`).:
    ```json
    {
        "terminal.integrated.shell.windows": "cmd.exe",
        "terminal.integrated.env.windows": {
        "CMDER_ROOT": "<path to cmder>/cmder"
        },
        "terminal.integrated.shellArgs.windows": [
        "/k <path to cmder>/cmder/vendor/init.bat"
        ],
    }
    ```

## Configuring `cmake-tools`

- The compiler/linker are specified via the active `cmake-tools` "kit".  MSVC compilers are discovered with the help of `vswhere` (bundled).

- By default `cmake-tools` selects `Ninja` as the generator. To override add the settings `<path to project>/.vscode/settings.json`:
    ```json
    "C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",
    
    "cmake.generator" : "Visual Studio 15 2017 Win64",
    "cmake.configureOnOpen": false,
    ```
  (of course only the second setting is directly relevant to forcing the generator).

## Configuring the `CMake` project

### bool options

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

### Defining dropdown options

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

### Setting Options with `cmake-tools`

- Add the option names and their settings to `<path to project>/.vscode/settings.json`:
    ```json
    {
        ...
        "cmake.configureSettings": {
        "USE_LIB_A" : "ON"
        },
        ...
    }
    ```

### Setting the Build Directory with `cmake-tools`

- Add:
    ```json
    {
        ...
        "cmake.buildDirectory": "${workspaceRoot}/<relative bin path>",
        ...
    }
    ```
    *n.b. that ${workspaceRoot} is the parent of the `/.vscode` folder*

## Configuring the CPP project

### Shared libs

- By default symbols in a shared library are not available on windows (requiring `declspec`).  Set:
    ```
    CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=ON
    ```
    or equivalently in the `settings.json`:
    ```json
    {
        "cmake.configureSettings": {
        ...
        "CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS" : "ON",
        ...
        },
    }
    ```


### an example lib/app skeleton

- File Structure

```
C:\USERS\COLINRAWLINGS\DESKTOP\TEST_CMAKE_TOOLS
│   .gitignore
│   CMakeLists.txt
│
├───app
│   │   CMakeLists.txt
│   │
│   └───src
│           main.cpp
│
├───lib_a
│   │   CMakeLists.txt
│   │
│   ├───include
│   │       a_lib.h
│   │
│   └───src
│           a_lib.cpp
```

- Top level `CMakeLists.txt`
    ```cmake
        project(test_cmake_tools)
        add_subdirectory(lib_a)
        add_subdirectory(app)
    ```
    - Define `lib_a` first since it will be needed by `àpp`

- `lib_a`'s `CMakeLists.txt`
    ```cmake
    add_library(lib_a STATIC)

    target_sources(lib_a PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/a_lib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/a_lib.h)

    target_include_directories(lib_a PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
    ```
    - Mark the header files which will be used externally with `PUBLIC`.
    - Use absolute paths to files
    - Do not use legacy `cmake` commands like `include_directories()`: 
      <https://github.com/vector-of-bool/vscode-cmake-tools/issues/481#issuecomment-406787695>

- `app`'s `CMakeLists.txt`
    ```cmake
    add_executable(main)

    target_sources(main PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

    target_link_libraries(main lib_a)
    ```
    - Do not redefine the include directories of `lib_a`.
    - Including the header files in `target_sources()` can help IDE's
    - The arguments for `target_sources()` will typically only be non-private in the case of header only libraries (public headers are defined via `PUBLIC` entries in `target_include_directories()`)
    - To use `lib_a` in `main.cpp`:
        ```cpp
        #include <a_lib.h>
        ```
      

## IDE Usage

- A useful `cmake-tools` command is: 
    ```
    CMake: Delete cached build settings and reconfigure
    ```
- *Don't* use `tasks.json` to configure the debugging, this should be left to `cmake-tools`.
- The core functionality (build and debug) can be triggered from the bar at the bottom of the application.  
- Build and Debug are buttons which start the activity the configuration (i.e. the targets) are shown as dropdown's to the right of their buttons.  