#include "image.h"

namespace wb {

Image::Image(void* data, uint width, uint height, uint pitch, PixelFormat format)
	: data((uchar*)data), width(width), height(height), pitch(pitch), format(format) {
	assert(data);
}

Vec4f Image::getPixel(int x, int y) const {

	if (x < 0 || x >= width || y < 0 || y >= height) return {};

	uchar* p = data + y * pitch + x * bytesPerPixel(format);
	switch (format) {
	case PixelFormat::alpha8:
		return Vec4f(0, 0, 0, p[0] / 255.0f);
	case PixelFormat::intensity8:
		return Vec4f(p[0] / 255.0f, p[0] / 255.0f, p[0] / 255.0f, 1);
	case PixelFormat::intensityAlpha16:
		return Vec4f(p[0] / 255.0f, p[0] / 255.0f, p[0] / 255.0f, p[1] / 255.0f);
	case PixelFormat::rgb24:
		return Vec4f(p[0] / 255.0f, p[1] / 255.0f, p[2] / 255.0f, 1);
	case PixelFormat::rgba32:
		return Vec4f(p[0] / 255.0f, p[1] / 255.0f, p[2] / 255.0f, p[3] / 255.0f);
	case PixelFormat::r32f:
		return Vec4f(*(float*)p, 0, 0, 1);
	case PixelFormat::srgb24:
	case PixelFormat::srgba32:
	case PixelFormat::rgba64f:
	case PixelFormat::depth32f:
		panic("TODO");
	}
	return {};
}

Vec4f Image::getPixel(float x, float y) const {
	float fx = std::floor(x);
	float fy = std::floor(y);
	int ix = int(fx);
	int iy = int(fy);
	auto x0 = getPixel(ix, iy);
	auto x1 = getPixel(ix + 1, iy);
	auto y0 = (x1 - x0) * (x - fx) + x0;
	auto x2 = getPixel(ix, iy + 1);
	auto x3 = getPixel(ix + 1, iy + 1);
	auto y1 = (x3 - x2) * (x - fx) + x2;
	return (y1 - y0) * (y - fy) + y0;
}

void Image::setPixel(int x, int y, CVec4f pixel) const {

	if (x < 0 || x >= width || y < 0 || y >= height) return;

	uchar* p = data + y * pitch + x * bytesPerPixel(format);
	switch (format) {
	case PixelFormat::alpha8:
		p[0] = std::round(pixel.w * 255.0f);
		return;
	case PixelFormat::intensity8:
		p[0] = std::round(pixel.x * 255.0f);
		return;
	case PixelFormat::intensityAlpha16:
		p[0] = std::round(pixel.x * 255.0f);
		p[1] = std::round(pixel.w * 255.0f);
		return;
	case PixelFormat::rgb24:
		p[0] = std::round(pixel.x * 255.0f);
		p[1] = std::round(pixel.y * 255.0f);
		p[2] = std::round(pixel.z * 255.0f);
		return;
	case PixelFormat::rgba32:
		p[0] = std::round(pixel.x * 255.0f);
		p[1] = std::round(pixel.y * 255.0f);
		p[2] = std::round(pixel.z * 255.0f);
		p[3] = std::round(pixel.w * 255.0f);
		return;
	case PixelFormat::r32f:
		*(float*)p = pixel.x;
		return;
	case PixelFormat::srgb24:
	case PixelFormat::srgba32:
	case PixelFormat::rgba64f:
	case PixelFormat::depth32f:
		panic("TODO");
	}
}

uint bytesPerPixel(PixelFormat format) {
	switch (format) {
	case PixelFormat::alpha8:
	case PixelFormat::intensity8:
		return 1;
	case PixelFormat::intensityAlpha16:
		return 2;
	case PixelFormat::rgb24:
	case PixelFormat::srgb24:
		return 3;
	case PixelFormat::rgba32:
	case PixelFormat::srgba32:
	case PixelFormat::r32f:
	case PixelFormat::depth32f:
		return 4;
	case PixelFormat::rgba64f:
		return 8;
	}
	panic("OOPS");
}

} // namespace wb
