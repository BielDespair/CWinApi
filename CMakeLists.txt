cmake_minimum_required(VERSION 4.2)

project(Engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Engine WIN32 src/main.cpp
    src/math/Vector.cpp
    src/math/mat4.cpp
    src/render/renderer.cpp
    src/game/game.cpp
    src/render/Shader.cpp
    src/render/buffers/VBO.cpp
    src/render/buffers/EBO.cpp
    src/render/buffers/VAO.cpp
    src/graphics/triangulation.cpp
    src/graphics/Camera.cpp
    src/graphics/shapes/primitives.cpp
    src/graphics/Mesh.cpp
    src/input/input.cpp
    src/game/player/Player.cpp
    src/render/Model.cpp
    )

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

target_link_libraries(Engine PRIVATE glad opengl32)

target_include_directories(Engine PRIVATE external)
target_include_directories(Engine PRIVATE src)





add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)