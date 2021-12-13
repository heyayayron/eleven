# Eleven

An experiment in agnostic graphics API rendering.
Inspired by BGFX https://github.com/bkaradzic/bgfx but not using any of the source.

## Goals

* Define a primitive via an abstraction
* Define a textured quad via an abstraction
* Define a shader via an abstraction
* The ability to render a primtive, textured quad or shader then switch backends without any difference (platform permitting).
* Switch backends at runtime (ignoring application state)

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