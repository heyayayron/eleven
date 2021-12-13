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

# ADD ASSETS
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenGL REQUIRED)

add_executable(eleven main.cpp src/Application.cpp src/Application.h src/Backend/OpenGL/OpenGLRenderer.cpp src/Backend/OpenGL/OpenGLRenderer.h src/Eleven.h src/Core/linmath.h src/Backend/Abstractions/IRendererAPI.h src/Backend/DirectX12/DirectXRenderer.cpp src/Backend/DirectX12/DirectXRenderer.h vendor/dxsdk/src/dxguids.cpp src/Core/ElevenMath.h src/elpch.cpp src/elpch.h src/Utility/Helpers.h src/Core/Core.cpp src/Core/Core.h src/Core/Buffer.h src/Backend/Vulkan/VulkanRenderer.cpp src/Backend/Vulkan/VulkanRenderer.h src/Backend/OpenGL/OpenGLBuffer.cpp src/Backend/OpenGL/OpenGLBuffer.h src/Backend/OpenGL/OpenGLShader.cpp src/Backend/OpenGL/OpenGLShader.h src/Backend/Abstractions/IShader.h)

target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/dxguid.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3d10.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dx10.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3d11.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dx11.lib)
target_link_libraries(eleven ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dxsdk/lib/d3dcompiler.lib)
target_link_libraries(eleven glad)
target_link_libraries(eleven OpenGL::GL)
target_link_libraries(eleven glfw)