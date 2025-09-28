#include <stdexcept>
#include <string>
#include <fstream>

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

	window = glfwCreateWindow(renderer->previewwidth, renderer->previewheight, "Preview", NULL, NULL);
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

void WindowManager::render(Scene scene, bool framebuffer) {
	if (framebuffer) {
		windowRenderer->bindFramebuffer();
		glViewport(0, 0, windowRenderer->width, windowRenderer->height);
	} else {
		windowRenderer->unbindFramebuffer();
		glViewport(0, 0, windowRenderer->previewwidth, windowRenderer->previewheight);	
	}
	windowRenderer->render(scene);
}

void WindowManager::push() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

Renderer::Renderer(VideoConsts consts) {
	previewwidth = consts.previewwidth;
	previewheight = consts.previewheight;
	width = consts.width;
	height = consts.height;
}

void Renderer::initFramebuffer() {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Framebuffer is not complete.");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::bindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::unbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Renderer::~Renderer() {
	glDeleteFramebuffers(1, &fbo);
}

void Renderer::render(Scene scene) {
	glClearColor(scene.background.x, scene.background.y, scene.background.z, scene.background.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::loadShaders(std::string vertexPath, std::string fragmentPath) {
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);

	std::string vertexString, fragmentString, str;
	while (std::getline(vertexFile, str)) {
		vertexString += str + "\n";
	}
	
	while (std::getline(fragmentFile, str)) {
		fragmentString += str + "\n";
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char * vertexCString = vertexString.c_str();
	const char * fragmentCString = fragmentString.c_str();

	glShaderSource(vertexShader, 1, &vertexCString, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentCString, nullptr);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		throw std::runtime_error((std::string)"Failed to compile vertex shader. " + infoLog);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		throw std::runtime_error((std::string)"Failed to compile fragment shader. " + infoLog);
	}

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shader, 512, nullptr, infoLog);
	    throw std::runtime_error((std::string)"Failed to link shader. " + infoLog);
	}

	glUseProgram(shader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}