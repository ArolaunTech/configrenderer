#include <GLFW/glfw3.h>

#include "../types/vector.h"

#ifndef RENDER_H
#define RENDER_H

struct RenderConsts {
	Vector4 background;
};

class Renderer {
	Vector4 background;

public:
	Renderer(RenderConsts renderconsts);

	void render();
};

class WindowManager {
private:
	GLFWwindow* window;
	Renderer* windowRenderer;
public:
	WindowManager(Renderer* renderer);
	~WindowManager();

	bool shouldClose();
	void render();
	void push();
};

#endif