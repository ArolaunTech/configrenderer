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
	"src/video/videowriter.cpp"
	"src/video/videowriter.h"
	"src/types/vector.h"
)

add_subdirectory("glfw-3.4")

add_library (glad STATIC "glad/src/glad.c")
target_include_directories(glad PUBLIC "glad/include")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavcodec
    libavformat
    libswscale
)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-Wall temp)

if(temp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

add_executable(configrender ${render_sources} ${PROJECT_PATH})
target_link_libraries(configrender glfw glad PkgConfig::LIBAV)

target_include_directories(configrender PUBLIC "glad/include" "/usr/local/Cellar/ffmpeg/8.0_1/include")