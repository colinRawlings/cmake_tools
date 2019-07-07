# msvc++ and cmake and vscode

## Configuring `vs code`
- Useful extensions:
    - `C/C++` (by microsoft): intellisense, debugger, code browsing
    - `Python` (by microsoft)
    - `cmake-tools`: include path determination from cmake files, debugger configurations
    - `cmake` (by twxs): syntax highlighting and command completion
    - `cmake format`: auto indentation
    - `GitLens`
    - `Graphviz Preview`: preview `.dot` file including those created by boost test.

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
- To improve clarity of the tree view:
    ```json
    "workbench.tree.indent": 16,
    ```

## Configuring the Visual Studio Tool Chain

- Using the VS2015 installer 
  - install: `Programming Languages/Visual C++`
  - install: `Windows and Web Development/Universal Windows App Development Tools/Windows 10 SDK`
    - *This is more subtle. Compiling etc. works without it but `Intellisense` complains about missing CRT headers (e.g. `corecrt.h`) and then disables the on-the-fly static checking ("red error squiggles").*

## Configuring `Graphviz Preview`
- Install [Graphviz](https://graphviz.gitlab.io/_pages/Download/Download_windows.html)
- Configure the path in the user wide `settings.json`:
    ```json
    "graphvizPreview.dotPath": "C:/Program Files (x86)/Graphviz2.38/bin/dot.exe",
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

- The `cmake-tools` kit `Visual Studio 14.0 - x86_amd64` uses the x86 build of the compilers to       build an amd64 compatible binary.  Note the settings in the kit are overriden if the `Visual Studio` generator is used.

## clcache

- work path to cl: `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64\CL.exe`
- installed following [cmake instructions](https://github.com/frerich/clcache/wiki/Integration#cmake)
- clcache_bin: `C:/ProgramData/chocolatey/bin/clcache.exe`
- n.b. install binary using chocolatey approach as this avoids the python2 issues inherent in the pip approach.n.b. install binary using chocolatey approach as this avoids the python2 issues inherent in the pip approach.

### Installation (Recommended)

- Install binary using `chocolatey` (as this avoids the need for python3 on the path which is not compatible with S4L development).
    ```cmd
    curl -L https://github.com/frerich/clcache/releases/download/v4.2.0/clcache.4.2.0.nupkg --output clcache.4.2.0.nupkg
    choco install clcache --source=.
    ```
- Follow the Integration for [Visual Studio instructions](https://github.com/frerich/clcache/wiki/Integration#integration-for-visual-studio):
    1. Rename `cl.exe` to e.g. `cl_original.exe`
    2. Rename `cl.exe.config` to e.g. `cl_original.exe.config`
    3. Copy the generated `clcache.exe` file `to cl.exe`
    4. Set CLCACHE_CL environment variable to point to `cl_original.exe`.

    *Additional notes*:
    1. The path to the relevant `cl.exe` can be found by running a configuration.
    3. the Choco `clcache.exe` binary relies on content it expects to find in `..\lib\clcache`.  
        - Thus this `lib\clcache` folder must also be copied to the parent of the folder containing `cl.exe`.
    4. To check everything is working, start a developer command prompt and run:
        `cl.exe`
        - In the output you should see the "fake" `cl.exe` (`clcache.exe`) start then call the real `cl.exe` (`cl_original.exe`) who should complain that no source file was specified. 

- For S4L you need to significantly increase the cache size (seems to need about 13GB per configuration):
    ```cmd
    clcache -M 13000000
    ```
    - You can check the result of this command as well as other aspects of its performance using:
        ```cmd
        clcache -s
        ```

### Alternative (No messing with the cl.exe folder)

- Set environment variable `clcache_cl` to `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64\cl.exe`
- Configure as normal
- Build with:
    ```cmd
    $ "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat" -arch=x64
    $ MSBuild.exe /p:CLToolExe=clcache.exe /p:CLToolPath=C:\ProgramData\chocolatey\bin /property:Configuration=Release <path to solution>.sln
    ```



## Ninja

- To install ninja (as admin):
    ```cmd
    $ choco install ninja
    ```

- It can be challenging to ensure that the correct byte order is picked up.  In particular:
    - `cmake` tests: `.../x32/cl.exe` not `.../x64/cl.exe`
    - `find_boost` can fail when it looks for `x32` versions of the library.

- A workaround is to run a clean configure (build folder deleted) in a cmd shell that has the VS variables set:
    - For the non-cross compiled version type: `Native ... ` into the windows search bar or run the corresponding scripts.
    - for VS2017:
    ```bash
    "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\vsdevcmd" -arch=x64
    ```
    - on ZMT machine (VS2015):
    ```bash
     "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\bin\\x86_amd64\\vcvarsx86_amd64.bat"
    ```
    (this is the cross compile version: x86 binaries build amd64 binaries)

- Check that the correct byte order has been built: `dumpbin /all C:\_dev\s4l_ninja\_build\SuperMash\SuperMash\XCore\CMakeFiles\XCore.dir\AbstractObserver.cpp.obj > c:\temp\AO_dmp.txt`

- Single target build:
    ```
    cmake --build . --target D -- -j7
    ```
    or

    ```
    ninja -j7 D
    ```

- TODO: document kit configuration for Ninja (setting env:CC and env: CXX correctly).

- After this can configure (but not clean and configure) from within `code`

- For some reason with shared libs the variable `CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS` does not get respected leading to an absence of `.lib` files (these are not created if the dll does not export any symbols).  The build succeeds but then the linking fails.

## Configuring `clang-format`

- Install llvm.

- Set as formatter:

    ```json
    "[cpp]": {
      "editor.defaultFormatter": "xaver.clang-format",
    },
    "clang-format.executable": "<path to LLVM>/bin/clang-format.exe",
    "editor.formatOnSave": true,
    "editor.formatOnType": true
    ```

- Format is taken from the first file with the name `_clang_format` or `.clang_format` encountered searching through the parent directories.

- Useful hints can be obtained with:
    - `clang-format.exe -dump-config -style=<style-of-interest>`
    - [this interactive webpage](https://clangformat.com/)

- Complete settings are described in the [documentation](https://releases.llvm.org/8.0.0/tools/clang/docs/ClangFormatStyleOptions.html)

- For Visual Studio 2015 it is necessary to first install [the extension](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat) and then run the repair tool (`[add remove programs/VS2015/Repair]`) to get the  menu items to appear.


## Configuring the `vscode` C++ extension

- Force intellisense by disabling fallback to the tag parser:
    ```json
    "C_Cpp.intelliSenseEngine" : "Default",
    "C_Cpp.intelliSenseEngineFallback": "Disabled",
    ```

## Configuring the `CMake` project

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

## Configuring Debuggers with command line options

- For targets not requiring command line arguments `cmake-tools` provides a graphical configuration.

- For command line arguments a good starting point for `.vscode/launch.json` is:

    ```json
    {
        "version": "0.2.0",
        "configurations":
        [
            {
                "name": "Test Runner Launch",
                "type": "cppvsdbg",
                "request": "launch",
                "program": "${workspaceFolder}/<path to test runner>/test_runner.exe",
                "args": [
                    "--color_output=1",
                    "--log_level=all",
                    "--run_test=<filter>",
                ],
                "stopAtEntry": false,
                "cwd": "${workspaceFolder}",
                "environment": [],
                "logging": {
                    "moduleLoad": false
                },
                "externalConsole": false,
            }
        ]
    }
    ```
    *note disabling of moduleLoad logging*


## Incremental Builds

### `vswhere.exe`


## Code Formating

### Installing `clang-format`


### Settings configuration
      

## IDE Usage

- A useful `cmake-tools` command is: 
    ```
    CMake: Delete cached build settings and reconfigure
    ```
- If command line arguments are not required it is not necessary to use `tasks.json` to configure the debugging.
- The core functionality (build and debug) can be triggered from the bar at the bottom of the application.  
- Build and Debug are buttons which start the activity the configuration (i.e. the targets) are shown as dropdown's to the right of their buttons.  



## Appendix

### Defining cmake options

#### bool options

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

#### Defining dropdown options

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

### Creating a binary directory

- There are a few ways to get a folder containing all exectuables and dll's.  
    - Lots of post build `copy-directory` commands
    - Lots of setting of the `runtime_output_directory` properties of the targets (provides fine grained control)
    - Setting the variable which is used to initialise target properties:
        ```cmake
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
        ```
        `PROJECT_BINARY_DIR` is the build directory.
        

### An example lib/app cmake skeleton

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
    add_library(lib_a)

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

### CMake Projects with boost

- Build boost (see project help).
    - [download .7z archive](https://www.boost.org/) and extract with 7zip (much faster).
    - run: `<path to boost>/bootstrap.bat`
    - run the build: 
        ```bash
        b2.exe --with-filesystem --with-test --with-regex --with-chrono toolset=msvc-14.1 address-model=64 architecture=x86 link=shared threading=multi
        ```
        *n.b. the suprising omission of hyphens when specifying the properties.  This omission is also present in the output from `b2.exe --help`.  With the hyphens (e.g. `--link=shared`) the settings appeared to be ignored.*

- Declare settings used during the boost build in the cmake file.:
    ```cmake
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_LIBS OFF)
    ```

- Find the library by defining an appropriate `BOOST_DIR`
    ```cmake
    set(BOOST_INCLUDEDIR ${BOOST_DIR})
    set(BOOST_LIBRARYDIR ${BOOST_DIR}/stage/lib)
    find_package(Boost COMPONENTS system filesystem REQUIRED)
    ```

    - If this fails retry with the following inserted before `boost` related commands:
    ```cmake
    set(Boost_DEBUG 1)
    ```

- Use:
    ```cmake
    target_link_libraries(main Boost::system Boost::filesystem)
    ```
    If this doesn't work ("missing find_package() call").  [Fall back to](https://cliutils.gitlab.io/modern-cmake/chapters/packages/Boost.html):
    ```cmake
    target_link_libraries(lib_a ${Boost_LIBRARIES})
    target_include_directories(lib_a PRIVATE ${Boost_INCLUDE_DIRS})
    ```

- For dynamic linking:
    ```cmake
    target_compile_definitions(my_lib PUBLIC BOOST_ALL_DYN_LINK)
    ```

- To run the libraries need to be copied to the bin folder:
    ```cmake
    add_custom_command(TARGET main POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory ${BOOST_LIBRARYDIR}
                     $<TARGET_FILE_DIR:main>)
    ```
