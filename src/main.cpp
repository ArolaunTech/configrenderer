#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern "C" {
	#include <libavcodec/avcodec.h>
}

#include "scene/scene.h"
#include "project.h"

int main() {
	const AVCodec* encoder = avcodec_find_encoder(AV_CODEC_ID_H265);
	if (!encoder) {
		std::cerr << "Encoder not initialized.\n";
		return 1;
	}

	Scene mainscene;
	setup(mainscene);

	if (!glfwInit()) {
		std::cerr << "Initialization of glfw failed.\n";
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}