#include <string>

#include "src/project.h"
#include "src/scene/scene.h"
#include "src/video/videowriter.h"
#include "src/types/vector.h"

void setup(Scene& scene, double time) {
	scene.background = Vector4 {time, 0.1, 0.1, 1};
}

VideoConsts setvideoconsts() {
	VideoConsts out;

	out.width = 1920;
	out.height = 1080;
	out.framerate = 30;
	out.frames = out.framerate * 10;
	out.previewwidth = 640;
	out.previewheight = 480;
	out.filepath = "test.mp4";

	out.maxvertices = 1024;

	return out;
}