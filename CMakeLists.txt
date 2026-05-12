cmake_minimum_required(VERSION 3.12)
project(njako C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

add_library(toolbox_object OBJECT
        src/toolbox/hashArray.c
        src/toolbox/pVoidArray.c
)

add_library(renderer_object OBJECT
        src/renderer/mesh.c
        src/renderer/shader.c
        src/renderer/texture.c
        src/renderer/geometry/baseGeometry.c
)

add_library(scene_object OBJECT
        src/scene/scene.c
        src/scene/sceneManager.c
)

add_library(platform_object OBJECT
    src/platform.c
)

add_library(main_object OBJECT
        src/main.c
)

target_include_directories(toolbox_object PRIVATE
        ${PROJECT_SOURCE_DIR}/src/toolbox
)

target_include_directories(renderer_object PRIVATE
        ${PROJECT_SOURCE_DIR}/src/toolbox
        ${PROJECT_SOURCE_DIR}/src/renderer
        ${PROJECT_SOURCE_DIR}/third_party
)

target_include_directories(scene_object PRIVATE
        ${PROJECT_SOURCE_DIR}/src/scene
        ${PROJECT_SOURCE_DIR}/src
)

target_include_directories(platform_object PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_include_directories(main_object PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/scene
)

add_executable(my_program
        $<TARGET_OBJECTS:main_object>
        $<TARGET_OBJECTS:renderer_object>
        $<TARGET_OBJECTS:toolbox_object>
        $<TARGET_OBJECTS:scene_object>
        $<TARGET_OBJECTS:platform_object>
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(my_program PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
        m
)

target_compile_definitions(my_program PRIVATE
        GLEW_STATIC
)