#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

	renderer.loadShaders("src/shaders/main.vert", "src/shaders/main.frag");
	renderer.initFramebuffer();

	double time = 0;
	int frames = 0;
	std::vector<GLubyte> pictureData(videoconsts.width * videoconsts.height * 4, 0);

	while (!windowmanager.shouldClose()) {
		Scene renderScene = setup(time);

		windowmanager.render(renderScene, true);

		videowriter.getDataFromFramebuffer(pictureData.data());
		videowriter.setFramePts(frames);
		videowriter.writeStoredFrame();

		windowmanager.render(renderScene, false);
		windowmanager.push();

		time += frametime;
		frames++;

		if (frames == videoconsts.frames) break;
	}
}