#include <iostream>
#include <stdexcept>
#include <string>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern "C" {
	#include <libavcodec/avcodec.h>
}

#include "scene/scene.h"
#include "video/videowriter.h"
#include "render/render.h"
#include "project.h"

int main() {
	VideoConsts videoconsts = setvideoconsts();
	VideoWriter videowriter(videoconsts);

	double frametime = 1 / (double)videoconsts.framerate;

	Renderer renderer(videoconsts);
	WindowManager windowmanager(&renderer);

	renderer.loadShaders("", "");
	renderer.initFramebuffer();

	double time = 0;
	int frames = 0;

	while (!windowmanager.shouldClose()) {
		windowmanager.render(setup(time));
		windowmanager.push();

		time += frametime;
		frames++;

		if (frames == videoconsts.frames) break;
	}
}