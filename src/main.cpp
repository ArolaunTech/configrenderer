#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern "C" {
	#include <libavcodec/avcodec.h>
}

#include "scene/scene.h"
#include "video/videowriter.h"
#include "project.h"

int main() {
	VideoConsts videoconsts = setconsts();
	VideoWriter videowriter(videoconsts);

	Scene mainscene;
	setup(mainscene);

	if (!glfwInit()) {
		std::cerr << "Initialization of glfw failed.\n";
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Preview", NULL, NULL);
	if (!window) {
		std::cerr << "Window creation failed.\n";
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}