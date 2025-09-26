#include <GLFW/glfw3.h>

#include "../scene/scene.h"

#ifndef RENDER_H
#define RENDER_H

class Renderer {
public:
	Renderer();

	void render(Scene scene);
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