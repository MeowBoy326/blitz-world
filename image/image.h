#pragma once

#include <core/core.hh>
#include <geom/geom.hh>

namespace wb {

WB_SHARED_CLASS(Image);

enum PixelFormat { alpha8, intensity8, intensityAlpha16, rgb24, srgb24, rgba32, srgba32, r32f, depth32f, rgba64f };

uint bytesPerPixel(PixelFormat format);

class Image : public Shared {
public:
	uchar* const data;
	uint const width;
	uint const height;
	uint const pitch;
	PixelFormat const format;

	Image(void* data, uint width, uint height, uint pitch, PixelFormat format);

	void setPixel(int x, int y, CVec4f pixel) const;

	Vec4f getPixel(int x, int y) const;
	Vec4f getPixel(float x, float y) const;
};

} // namespace wb
