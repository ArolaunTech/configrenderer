cmake_minimum_required(VERSION 3.25)

project(configrender LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DPROJECT_PATH="${PROJECT_PATH}")

set(
	render_sources
	"src/main.cpp"
	"src/project.h"
	"src/render/render.cpp"
	"src/render/render.h"
	"src/scene/scene.cpp"
	"src/scene/scene.h"
)

add_subdirectory("glfw-3.4")

add_library (glad STATIC "glad/src/glad.c")
target_include_directories(glad PUBLIC "glad/include")

add_executable(configrender ${render_sources} ${PROJECT_PATH})
target_link_libraries(configrender glfw glad)

target_include_directories(configrender PUBLIC "glad/include" "/usr/local/Cellar/ffmpeg/8.0_1/include")