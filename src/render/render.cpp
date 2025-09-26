#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "../scene/scene.h"

WindowManager::WindowManager(Renderer* renderer) {
	windowRenderer = renderer;

	if (!glfwInit()) {
		throw std::runtime_error("Initialization of glfw failed.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Preview", NULL, NULL);
	if (!window) {
		throw std::runtime_error("Window creation failed.");
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
}

WindowManager::~WindowManager() {
	glfwTerminate();
}

bool WindowManager::shouldClose() {
	return glfwWindowShouldClose(window);
}

void WindowManager::render(Scene scene) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	windowRenderer->render(scene);
}

void WindowManager::push() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

Renderer::Renderer() {}

void Renderer::render(Scene scene) {
	glClearColor(scene.background.x, scene.background.y, scene.background.z, scene.background.w);
	glClear(GL_COLOR_BUFFER_BIT);
}