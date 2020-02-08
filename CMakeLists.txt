cmake_minimum_required(VERSION 3.12.0)
project(Panorama CXX)
add_definitions(-Wall -O2 -fexceptions)

set(THIRD_PARTIES ${CMAKE_SOURCE_DIR}/thirdParties)

#   set(BSF_DIRECTORY ${THIRD_PARTIES}/bsf)
message(${THIRD_PARTIES})

#   include(${BSF_DIRECTORY}/Source/CMake/ProjectDefaults.cmake)
include_directories(thirdParties/assimp/include)
include_directories(thirdParties/stb)

set(PROJECT_NAME Panorama)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

add_executable(Panorama
        main.cpp
        game/gameCore/Game.cpp
        game/gameCore/Game.hpp
        game/gameWorld/movingThings/player/Player.cpp
        game/gameWorld/movingThings/player/Player.hpp
        game/gameProperties/GameProperties.cpp
        game/gameProperties/GameProperties.hpp
        game/mathematics/matrices/Matrics.cpp
        game/mathematics/matrices/Matrics.hpp
        game/mathematics/operations/Sqrt.cpp
        game/mathematics/operations/Sqrt.hpp
        game/mathematics/vectors/Vectors.cpp
        game/mathematics/vectors/Vectors.hpp
        game/gameWorld/movingThings/player/Player.cpp
        game/gameWorld/movingThings/player/Player.hpp
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
        graphics/textures/Texture.cpp
        graphics/textures/Texture.hpp
        game/mathematics/glm_c_wrapper.hpp
        game/mathematics/glm_c_wrapper.cpp
        game/fileIO/fastConfig/FastConfig.cpp
        game/fileIO/fastConfig/FastConfig.h
        graphics/mesh/Mesh.cpp
        graphics/mesh/Mesh.h
        game/gameCore/World/World.cpp
        game/gameCore/World/World.h
        graphics/mesh/MeshMisc.h
        game/gameCore/GGraph.cpp
        game/gameCore/GGraph.h
        game/gameCore/GGame.cpp
        game/gameCore/GGame.h
        game/gameWorld/movingThings/Entity.cpp
        game/gameWorld/movingThings/Entity.h
        game/gameWorld/movingThings/Point.h
        graphics/model/Model.cpp
        graphics/model/Model.h
        graphics/camera/Camera.cpp
        graphics/camera/Camera.h
        game/gameWorld/movingThings/FixedEntity.cpp
        game/gameWorld/movingThings/FixedEntity.h)

message(${ASSIMP_LIBRARIES})

target_link_libraries(Panorama m -lpthread)
target_link_libraries(Panorama glfw)
target_link_libraries(Panorama GLEW)
target_link_libraries(Panorama GL)
target_link_libraries(Panorama assimp)
target_link_libraries(Panorama ${ASSIMP_LIBRARIES}/assimp)

#   target_link_libraries(Panorama bsf)
#   add_engine_dependencies(Panorama)
#   add_dependencies(Panorama bsfFBXImporter bsfFontImporter bsfFreeImgImporter)
#   install_dll_on_build(Panorama ${BSF_DIRECTORY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")