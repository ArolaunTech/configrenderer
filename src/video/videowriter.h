#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

struct VideoConsts {
	int width;
	int height;
	int framerate;
};

class VideoWriter {
public:
	VideoWriter(VideoConsts parameters);
	~VideoWriter();
};

#endif