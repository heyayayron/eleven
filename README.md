# Eleven

An experiment in agnostic graphics API rendering.

## Requirements

The **vendor** directory needs the following dependencies

Optional:

    dxsdk/include
    dxsdk/lib
    dxsdk/src (for dxguids.cpp)

Required:

    glad/include
    glad/src
    glad/CMakeLists.txt

    glfw-3.3.5/include
    glfw-3.3.5/src
    glfw/CMakeLists.txt

## TODO

* Windowing 
* Backends
* Basic Renderer
    * OpenGL Renderer shouldn't use **GL_QUADS**
* Rendering pipeline specifics (Starting with OpenGL)