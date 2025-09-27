extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
}

#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

struct VideoConsts {
	int width;
	int height;
	int framerate;
	int frames;
	int previewwidth;
	int previewheight;
};

class VideoWriter {
private:
	AVCodecContext* context = nullptr;
	AVFrame* picture = nullptr;
public:
	VideoWriter(VideoConsts parameters);
	~VideoWriter();

	void writeFrame(AVFrame* frame);
};

#endif