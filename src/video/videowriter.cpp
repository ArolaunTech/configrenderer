#include <stdexcept>
#include <string>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
}

#include "videowriter.h"

VideoWriter::VideoWriter(VideoConsts parameters) {
	width = parameters.width;
	height = parameters.height;
	framerate = parameters.framerate;

	const AVCodec* encoder = avcodec_find_encoder(AV_CODEC_ID_H265);

	if (!encoder) {
		throw std::runtime_error("Failed to initialize encoder.");
	}

	context = avcodec_alloc_context3(encoder);
	if (!context) {
		throw std::runtime_error("Failed to create video context.");
	}

	context->width = width;
	context->height = height;
	context->time_base = (AVRational){1, parameters.framerate};
	context->framerate = (AVRational){parameters.framerate, 1};
	context->pix_fmt = AV_PIX_FMT_YUV420P;

	if (avcodec_open2(context, encoder, nullptr) < 0) {
		throw std::runtime_error("Could not open encoder.");
	}

	int ret = avformat_alloc_output_context2(
		&formatcontext, 
		nullptr, 
		nullptr, 
		parameters.filepath.c_str()
	);
	if (ret < 0 || formatcontext == nullptr) {
		throw std::runtime_error("Could not initialize format context.");
	}

	stream = avformat_new_stream(formatcontext, encoder);
	if (stream == nullptr) {
		throw std::runtime_error("Could not initialize video stream.");
	}

	if (avcodec_parameters_from_context(stream->codecpar, context) < 0) {
		throw std::runtime_error("Could not initialize parameters of videostream.");
	}

	if (avio_open(&formatcontext->pb, parameters.filepath.c_str(), AVIO_FLAG_WRITE) < 0) {
		throw std::runtime_error("Could not initialize avio.");
	}

	if (avformat_write_header(formatcontext, nullptr) < 0) {
		throw std::runtime_error("Could not write header in format context.");
	}

	sws = sws_getContext(
		width,
		height,
		AV_PIX_FMT_RGBA,
		width,
		height,
		AV_PIX_FMT_YUV420P,
		SWS_BICUBIC,
		nullptr,
		nullptr,
		nullptr
	);
	if (!sws) {
		throw std::runtime_error("Could not create sws context.");
	}

	picture = av_frame_alloc();
	if (!picture) {
		throw std::runtime_error("Could not allocate frame.");
	}

	picture->format = AV_PIX_FMT_YUV420P;
	picture->width = width;
	picture->height = height;
	
	if (av_frame_get_buffer(picture, 0) < 0) {
		throw std::runtime_error("Can't allocate the video frame data.");
	}

	if (av_frame_make_writable(picture) < 0) {
		throw std::runtime_error("Can't make frame writable.");
	}
}

VideoWriter::~VideoWriter() {
	writeFrame(nullptr);

	avcodec_free_context(&context);
	av_frame_free(&picture);
	av_packet_unref(&packet);
	sws_freeContext(sws);
	av_write_trailer(formatcontext);
	avformat_free_context(formatcontext);
}

void VideoWriter::writeStoredFrame() {
	writeFrame(picture);
}

void VideoWriter::writeFrame(AVFrame* frame) {
	if (avcodec_send_frame(context, frame) < 0 && frame != nullptr) {
		throw std::runtime_error("Failed to encode video.");
	}

	int ret;
	while (true) {
		ret = avcodec_receive_packet(context, &packet);

		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;
		if (ret != 0) throw std::runtime_error("Failed to receive packet.");

		av_packet_rescale_ts(&packet, { 1, framerate }, stream->time_base);
		packet.stream_index = stream->index;

		if (av_interleaved_write_frame(formatcontext, &packet) < 0) {
			throw std::runtime_error("Failed to write frame.");
		}
	}
}

void VideoWriter::setFramePts(int pts) {
	picture->pts = pts;
}

void VideoWriter::getDataFromFramebuffer(GLubyte* data) {
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	const int rgblinesize[1] = {4 * width};
	const uint8_t* rgbplanes[1] = {data};

	if (sws_scale(
		sws,
		rgbplanes,
		rgblinesize,
		0,
		height,
		picture->data,
		picture->linesize
	) < 0) {
		throw std::runtime_error("sws_scale returned an error.");
	}
}