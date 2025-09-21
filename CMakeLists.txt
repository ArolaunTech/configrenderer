cmake_minimum_required(VERSION 3.25)

project(
	configrender
	VERSION 0.0.1
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

set(
	render_sources
	"src/main.cpp"
)

add_executable(configrender ${render_sources})