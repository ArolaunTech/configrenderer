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

	RenderConsts renderconsts = setrenderconsts();

	Scene mainscene;
	setup(mainscene);

	Renderer renderer(renderconsts);
	WindowManager windowmanager(&renderer);

	while (!windowmanager.shouldClose()) {
		windowmanager.render();
		windowmanager.push();
	}
}