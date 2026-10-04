cmake_minimum_required(VERSION 3.12)
project(njako C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
# Все исходники
add_library(main OBJECT
        src/main.c
        src/platform.c
        src/scene/sceneManager.c
        src/scene/mainMenu/mainMenu.c
        src/scene/idle/idle.c
        src/toolbox/toolBox.c
        src/persons/createPersons.c
        src/persons/konata/konata.c
        src/scene/scnHashMap.c
)

add_subdirectory(src/containers)
target_link_libraries(main PRIVATE nonownContainers)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)
target_link_libraries(main PRIVATE raylib)

# Пути к заголовкам (ваши локальные + системные)
target_include_directories(main PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/scene
        ${PROJECT_SOURCE_DIR}/src/scene/idle
        ${PROJECT_SOURCE_DIR}/src/scene/mainMenu
        ${PROJECT_SOURCE_DIR}/src/toolbox
        ${PROJECT_SOURCE_DIR}/src/persons
        ${PROJECT_SOURCE_DIR}/src/persons/konata
)

add_executable(my_program)
target_link_libraries(my_program PRIVATE
    main
    raylib
    m
)

# Линковка с системными библиотеками
target_link_libraries(my_program PRIVATE
        m  # математическая библиотека
)