#include "src/project.h"
#include "src/scene/scene.h"
#include "src/video/videowriter.h"

void setup(Scene& mainscene) {

}

VideoConsts setconsts() {
	VideoConsts out;

	out.width = 1920;
	out.height = 1080;
	out.framerate = 30;

	return out;
}