cmake_minimum_required(VERSION 3.12)
project(njako C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
# Все исходники
add_library(main OBJECT
        src/main.c
        src/platform.c
        src/scene/scene.c
        src/scene/sceneManager.c
        src/scene/mainMenu/mainMenu.c
        src/scene/idle/idle.c
        src/toolbox/hashArray.c
        src/toolbox/pVoidArray.c
        src/toolbox/toolBox.c
        src/renderer/mesh.c
        src/renderer/shader.c
        src/renderer/texture.c
        src/renderer/geometry/baseGeometry.c
        src/persons/createPersons.c
        src/persons/konata/konata.c
)

# Пути к заголовкам (ваши локальные + системные)
target_include_directories(main PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/scene
        ${PROJECT_SOURCE_DIR}/src/scene/idle
        ${PROJECT_SOURCE_DIR}/src/scene/mainMenu
        ${PROJECT_SOURCE_DIR}/src/toolbox
        ${PROJECT_SOURCE_DIR}/src/persons
        ${PROJECT_SOURCE_DIR}/src/persons/konata
        ${PROJECT_SOURCE_DIR}/src/renderer
        ${PROJECT_SOURCE_DIR}/src/renderer/geometry
        ${PROJECT_SOURCE_DIR}/third_party/glew/include
        ${PROJECT_SOURCE_DIR}/third_party/freeglut/include
        ${PROJECT_SOURCE_DIR}/third_party
)

add_executable(my_program $<TARGET_OBJECTS:main>)

# Поиск системных библиотек
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

# Линковка с системными библиотеками
target_link_libraries(my_program PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
        m  # математическая библиотека
)

# Для статической линковки GLEW (опционально)
target_compile_definitions(my_program PRIVATE
        GLEW_STATIC
)