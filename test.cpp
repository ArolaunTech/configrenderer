#include "src/project.h"
#include "src/scene/scene.h"
#include "src/video/videowriter.h"
#include "src/types/vector.h"

Scene setup(double time) {
	Scene out;

	Vector4 bg;
	bg.x = 0.1; bg.y = 0.1; bg.z = 0.1; bg.w = 1;

	out.background = bg;

	return out;
}

VideoConsts setvideoconsts() {
	VideoConsts out;

	out.width = 1920;
	out.height = 1080;
	out.framerate = 30;

	return out;
}