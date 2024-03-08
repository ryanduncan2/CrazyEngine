cmake_minimum_required(VERSION 3.24.2)
project(CrazyEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenGL REQUIRED)

set(SRC_FILES
    src/Application.cpp

    src/Vendor/glad.cpp

    src/Core/Input.cpp
    src/Core/Clock.cpp

    src/Platform/PlatformWin32.cpp

    src/Graphics/Shader.cpp
    src/Graphics/Renderer2D.cpp
    src/Graphics/Texture.cpp
    src/Graphics/Buffers.cpp
    src/Graphics/RendererAPI.cpp
    src/Graphics/VertexArray.cpp
    src/Graphics/BufferLayout.cpp
    src/Graphics/TextureFont.cpp

    src/Graphics/OpenGL/OpenGLBuffers.cpp
    src/Graphics/OpenGL/OpenGLRendererAPI.cpp
    src/Graphics/OpenGL/OpenGLShader.cpp
    src/Graphics/OpenGL/OpenGLTexture.cpp
    src/Graphics/OpenGL/OpenGLVertexArray.cpp

    src/Math/Calculator.cpp
    src/Math/Vector2.cpp
    src/Math/Vector3.cpp
    src/Math/Vector4.cpp
    src/Math/Matrix4.cpp
    src/Math/Rectangle.cpp
    src/Math/Duration.cpp
)

add_library(CrazyEngine STATIC ${SRC_FILES})
target_include_directories(CrazyEngine PRIVATE include "${OPENGL_INCLUDE_DIR}")
target_link_libraries(CrazyEngine PRIVATE "${OPENGL_LIBRARIES}")