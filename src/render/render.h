#include <string>

#include <GLFW/glfw3.h>

#include "../scene/scene.h"
#include "../video/videowriter.h"

#ifndef RENDER_H
#define RENDER_H

class Renderer {
	unsigned int fbo;
public:
	int previewwidth;
	int previewheight;

	Renderer(VideoConsts consts);
	~Renderer();

	void initFramebuffer();
	void render(Scene scene);
	void loadShaders(std::string vertexPath, std::string fragmentPath);
};

class WindowManager {
private:
	GLFWwindow* window;
	Renderer* windowRenderer;
public:
	WindowManager(Renderer* renderer);
	~WindowManager();

	bool shouldClose();
	void render(Scene scene);
	void push();
};

#endif