#include <stdexcept>
#include <string>

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
}

#include "videowriter.h"

VideoWriter::VideoWriter(VideoConsts parameters) {
	const AVCodec* encoder = avcodec_find_encoder(AV_CODEC_ID_H265);

	if (!encoder) {
		throw std::runtime_error("Failed to initialize encoder.");
	}

	context = avcodec_alloc_context3(encoder);
	if (!context) {
		throw std::runtime_error("Failed to create video context.");
	}

	context->width = parameters.width;
	context->height = parameters.height;
	context->time_base = (AVRational){1, parameters.framerate};
	context->framerate = (AVRational){parameters.framerate, 1};
	context->pix_fmt = AV_PIX_FMT_YUV420P;

	if (avcodec_open2(context, encoder, nullptr) < 0) {
		throw std::runtime_error("Could not open encoder.");
	}

	picture = av_frame_alloc();
	if (!picture) {
		throw std::runtime_error("Could not allocate frame.");
	}

	picture->format = AV_PIX_FMT_YUV420P;
	picture->width = parameters.width;
	picture->height = parameters.height;
	
	if (av_frame_get_buffer(picture, 0) < 0) {
		throw std::runtime_error("Can't allocate the video frame data.");
	}
}

VideoWriter::~VideoWriter() {
	avcodec_free_context(&context);
	av_frame_free(&picture);
}

void VideoWriter::writeFrame(AVFrame* frame) {
	int ret = 0;
	
	if (ret < 0 && frame != nullptr) {
		throw std::runtime_error("Failed to encode video.");
	}

	AVPacket packet;
}