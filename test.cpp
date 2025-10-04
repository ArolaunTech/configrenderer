#include <string>

#include "src/project.h"
#include "src/scene/scene.h"
#include "src/video/videowriter.h"
#include "src/types/vector.h"
#include "src/geometry/mesh.h"
#include "src/geometry/defaultmeshes.h"

void setup(Scene& scene, double time) {
	scene.background = Vector4 {0.1, 0.1, 0.1, 1};

	scene.meshes = {cube(), cone(50)};

	scene.rotations = {rotateY(time) * rotateX(2 * time), rotateY(.5 * time) * rotateX(-time)};
	scene.translations = {translate(Vector3{-1, 0, -2}), translate(Vector3{1, 0, -2})};

	scene.view = identityMatrix(4);
	scene.perspective = perspective(90, 0.1, 10);
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

	out.maxtris = 1024;

	return out;
}