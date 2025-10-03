#include <string>

#include <GLFW/glfw3.h>

#include "../scene/scene.h"
#include "../video/videowriter.h"

#ifndef RENDER_H
#define RENDER_H

class Renderer {
	unsigned int fbo;

	unsigned int vao;
	unsigned int vboPosition;
	unsigned int vboNormal;

	unsigned int aspectLoc;
	unsigned int flipYLoc;
	unsigned int rotateLoc;
	unsigned int translateLoc;
	unsigned int viewLoc;
	unsigned int perspectiveLoc;
	unsigned int lightdirLoc;
	unsigned int lightcolorLoc;

	unsigned int maxtris;
public:
	int previewwidth;
	int previewheight;
	int width;
	int height;

	Renderer(VideoConsts consts);
	~Renderer();

	void initFramebuffer();
	void initBuffers();

	void bindFramebuffer();
	void unbindFramebuffer();

	void setAspect(double aspectratio);
	void setYFlip(bool yflip);

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
	void render(Scene scene, bool framebuffer);
	void push();
};

#endif