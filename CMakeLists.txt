cmake_minimum_required(VERSION 4.2)

project(Engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Engine WIN32 src/main.cpp
    src/math/vector.cpp
    src/render/renderer.cpp
    src/game.cpp
    src/render/Shader.cpp
    src/render/VBO.cpp
    src/graphics/triangulation.cpp
    src/render/EBO.cpp
    src/render/VAO.cpp
    )

add_executable(Testing src/testing.cpp src/graphics/triangulation.cpp src/math/vector.cpp)


add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

target_link_libraries(Engine PRIVATE glad opengl32)

target_include_directories(Testing PRIVATE include)
target_include_directories(Engine PRIVATE include)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders"
)