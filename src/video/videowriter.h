#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
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

	std::string filepath;
};

class VideoWriter {
private:
	int width;
	int height;
	int framerate;

	AVCodecContext* context = nullptr;
	AVFormatContext* formatcontext = nullptr;
	AVStream* stream = nullptr;
	AVFrame* picture = nullptr;
	AVPacket packet = {0};
	SwsContext* sws = nullptr;
public:
	VideoWriter(VideoConsts parameters);
	~VideoWriter();

	void writeFrame(AVFrame* frame);
	void writeStoredFrame();
	void setFramePts(int pts);
	void getDataFromFramebuffer(GLubyte* data);
};

#endif