#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "../scene/scene.h"
#include "../types/matrix.h"

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

		windowRenderer->setAspect((double)(windowRenderer->width) / (windowRenderer->height));
	} else {
		windowRenderer->unbindFramebuffer();
		glViewport(0, 0, windowRenderer->previewwidth, windowRenderer->previewheight);

		windowRenderer->setAspect((double)(windowRenderer->previewwidth) / (windowRenderer->previewheight));
	}
	windowRenderer->setYFlip(framebuffer);
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
	maxtris = consts.maxtris;
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

void Renderer::initBuffers() {
	glGenBuffers(1, &vboPosition);
	glGenBuffers(1, &vboNormal);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, 9 * maxtris * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, 9 * maxtris * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::bindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::unbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::setYFlip(bool yflip) {
	glUniform1f(flipYLoc, yflip ? -1 : 1);
}

void Renderer::setAspect(double aspectratio) {
	glUniform1f(aspectLoc, (GLfloat) aspectratio);
}

Renderer::~Renderer() {
	glDeleteFramebuffers(1, &fbo);
	glDeleteBuffers(1, &vboPosition);
	glDeleteBuffers(1, &vboNormal);
	glDeleteVertexArrays(1, &vao);
}

void Renderer::render(Scene scene) {
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glBufferSubData(GL_ARRAY_BUFFER, 0, scene.points.size() * sizeof(GLfloat), scene.points.data());

	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glBufferSubData(GL_ARRAY_BUFFER, 0, scene.points.size() * sizeof(GLfloat), scene.normals.data());

	glClearColor(scene.background.x, scene.background.y, scene.background.z, scene.background.w);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);

	std::array<GLfloat, 16> matrixdata;

	glUniform3f(lightdirLoc, 1.0, 1.0, 1.0);
	glUniform3f(lightcolorLoc, 1, 1, 1);

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			matrixdata[4 * j + k] = (GLfloat)scene.view.elements[j][k];
		}
	}

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, matrixdata.data());

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			matrixdata[4 * j + k] = (GLfloat)scene.perspective.elements[j][k];
		}
	}

	glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, matrixdata.data());

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			matrixdata[4 * j + k] = (GLfloat)scene.view.elements[j][k];
		}
	}

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, matrixdata.data());

	std::size_t nummeshes = scene.meshes.size();
	for (std::size_t i = 0; i < nummeshes; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrixdata[4 * j + k] = (GLfloat)scene.rotations[i].elements[j][k];
			}
		}

		glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, matrixdata.data());

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrixdata[4 * j + k] = (GLfloat)scene.translations[i].elements[j][k];
			}
		}

		glUniformMatrix4fv(translateLoc, 1, GL_FALSE, matrixdata.data());
		glDrawArrays(GL_TRIANGLES, scene.startindices[i] / 3, scene.sizes[i] / 3);
	}
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

	flipYLoc = glGetUniformLocation(shader, "flipY");
	if (flipYLoc == -1) {
		throw std::runtime_error("Could not find flipY.");
	}

	aspectLoc = glGetUniformLocation(shader, "scaleX");
	if (aspectLoc == -1) {
		throw std::runtime_error("Could not find aspect ratio.");
	}

	rotateLoc = glGetUniformLocation(shader, "rotate");
	if (rotateLoc == -1) {
		throw std::runtime_error("Could not find rotation matrix in shader.");
	}

	translateLoc = glGetUniformLocation(shader, "translate");
	if (translateLoc == -1) {
		throw std::runtime_error("Could not find translation matrix in shader.");
	}

	viewLoc = glGetUniformLocation(shader, "view");
	if (viewLoc == -1) {
		throw std::runtime_error("Could not find view matrix in shader.");
	}

	perspectiveLoc = glGetUniformLocation(shader, "perspective");
	if (perspectiveLoc == -1) {
		throw std::runtime_error("Could not find perspective matrix in shader.");
	}

	lightdirLoc = glGetUniformLocation(shader, "lightdir");
	if (lightdirLoc == -1) {
		throw std::runtime_error("Could not find lightdir matrix in shader.");
	}

	lightcolorLoc = glGetUniformLocation(shader, "lightcolor");
	if (lightcolorLoc == -1) {
		throw std::runtime_error("Could not find lightcolor matrix in shader.");
	}
}