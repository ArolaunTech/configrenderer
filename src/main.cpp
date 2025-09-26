#include <iostream>
#include <stdexcept>

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

	Renderer renderer;
	WindowManager windowmanager(&renderer);

	double time = 0;
	while (!windowmanager.shouldClose()) {
		windowmanager.render(setup(time));
		windowmanager.push();

		time += frametime;
	}
}