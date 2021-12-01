cmake_minimum_required(VERSION 3.19)
project(eleven)

set(CMAKE_CXX_STANDARD 20)

# IGNORE GLFW TESTS AND DOCS
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# ADD GLAD+GLFW
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw-3.3.5)

find_package(OpenGL REQUIRED)

add_executable(eleven main.cpp src/Application.cpp src/Application.h src/Renderer/OpenGLRenderer.cpp src/Renderer/OpenGLRenderer.h src/Eleven.h src/Renderer/linmath.h src/Renderer/IRendererAPI.h src/Renderer/DirectXRenderer.cpp src/Renderer/DirectXRenderer.h vendor/dxsdk/src/dxguids.cpp src/Core/Buffer.cpp src/Core/Buffer.h src/Core/ElevenMath.h)

target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/dxguid.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3d10.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dx10.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3d11.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dx11.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dcompiler.lib)
target_link_libraries(eleven glad)
target_link_libraries(eleven OpenGL::GL)
target_link_libraries(eleven glfw)