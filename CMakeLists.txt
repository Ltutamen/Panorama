cmake_minimum_required(VERSION 3.12)
project(Panorama CXX)


set(PROJECT_NAME Panorama)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

add_executable(Panorama
        main.cpp
        game/gameCore/Game.cpp
        game/gameCore/Game.hpp
        game/player/Player.cpp
        game/player/Player.hpp
        game/gameProperties/GameProperties.cpp
        game/gameProperties/GameProperties.hpp
        game/mathematics/matrices/Matrics.cpp
        game/mathematics/matrices/Matrics.hpp
        game/mathematics/operations/Sqrt.cpp
        game/mathematics/operations/Sqrt.hpp
        game/mathematics/vectors/Vectors.cpp
        game/mathematics/vectors/Vectors.hpp
        game/player/Player.cpp
        game/player/Player.hpp
        graphics/window/Window.cpp
        graphics/window/Window.hpp
        graphics/shaders/Shader.cpp
        graphics/shaders/Shader.hpp
        game/fileIO/logging/Logger.cpp
        game/fileIO/logging/Logger.hpp
        game/fileIO/logging/List/List.cpp
        game/fileIO/logging/List/List.hpp
        game/fileIO/logging/syncQueue/syncQueue.cpp
        game/fileIO/logging/syncQueue/syncQueue.hpp
        game/gameCore/inputHandling/inputHandler.cpp
        game/gameCore/inputHandling/inputHandler.hpp
        graphics/textures/Texture.cpp
        graphics/textures/Texture.hpp
        game/mathematics/glm_c_wrapper.hpp
        game/mathematics/glm_c_wrapper.cpp
        game/fileIO/fastConfig/FastConfig.cpp game/fileIO/fastConfig/FastConfig.h graphics/mesh/Mesh.cpp graphics/mesh/Mesh.h game/gameCore/World/World.cpp game/gameCore/World/World.h graphics/mesh/MeshMisc.h game/gameCore/GGraph.cpp game/gameCore/GGraph.h game/gameCore/GGame.cpp game/gameCore/GGame.h)


target_link_libraries(Panorama m -lpthread)
target_link_libraries(Panorama glfw)
target_link_libraries(Panorama GLEW)
target_link_libraries(Panorama GL)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")