cmake_minimum_required(VERSION 3.17)
project(Mass_Spring_Game)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/imgui)

set (MASS_SOURCE_FILES
        main.cpp
        vector2f.h
        mass_spring_system.cpp
        mass_spring_system.h)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw imgui glad)

add_executable(Mass_Spring_Game ${MASS_SOURCE_FILES})
target_include_directories(Mass_Spring_Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

add_definitions(-D IMGUI_IMPL_OPENGL_LOADER_GLAD)
