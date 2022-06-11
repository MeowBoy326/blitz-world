#include "glutils.h"

#include <stb/stb.hh>

#define USE_FILTER STBIR_FILTER_TRIANGLE

namespace wb {

void setGLTextureData(uint width, uint height, PixelFormat format, FilterFlags flags, const void* data) {

	if (!data) return;

	GLenum glTarget = GL_TEXTURE_2D;

	auto& glFormat = glPixelFormats[int(format)];

	uchar* mipData = (uchar*)data;

	if (glFormat.internalFormat == GL_SRGB8_ALPHA8 && data != nullptr) {
		mipData = (uchar*)malloc(width * 4 * height);
		for (uint y = 0; y < height; ++y) {
			uchar* dst = mipData + y * width * 4;
			const uchar* src = (uchar*)data + y * width * 4;
			for (uint x = 0; x < width; src += 4, dst += 4, ++x) {
				// ok, we want to premultiply rgb * alpha in linear space, but store srgb.
				// we can't just convert to linear and leave it as this can produce values > 255
				float a = src[3] / 255.0f;
				float r = std::pow(src[0] / 255.0f, 2.2f) * a;
				float g = std::pow(src[1] / 255.0f, 2.2f) * a;
				float b = std::pow(src[2] / 255.0f, 2.2f) * a;
				dst[0] = std::pow(r, 1 / 2.2f) * 255;
				dst[1] = std::pow(g, 1 / 2.2f) * 255;
				dst[2] = std::pow(b, 1 / 2.2f) * 255;
				dst[3] = src[3];
			}
		}
	}

	uint w = width;
	uint h = height;
	for (uint mipLevel = 0;; ++mipLevel) {

		glTexImage2D(glTarget, mipLevel, glFormat.internalFormat, w, h, 0, glFormat.format, glFormat.type, mipData);

		if ((flags & FilterFlags::mipmap) != FilterFlags::mipmap) break;

		if (w == 1 && h == 1) break;

		uint pw = w;
		uint ph = h;
		w = w > 1 ? w / 2 : w;
		h = h > 1 ? h / 2 : h;

		if (!mipData) continue;

		if (bytesPerChannel(format) != 1) {
			glGenerateMipmap(glTarget);
			break;
		}

		uchar* newData = (uchar*)malloc(w * bytesPerPixel(format) * h);

		if (glFormat.internalFormat == GL_SRGB8_ALPHA8) {

			stbir_resize_uint8_generic(mipData, pw, ph, 0, newData, w, h, 0, 4, 3, STBIR_FLAG_ALPHA_PREMULTIPLIED,
									   STBIR_EDGE_CLAMP, USE_FILTER, STBIR_COLORSPACE_SRGB, nullptr);

		} else if (glFormat.internalFormat == GL_SRGB8) {

			stbir_resize_uint8_generic(mipData, pw, ph, 0, newData, w, h, 0, 3, -1, STBIR_FLAG_ALPHA_PREMULTIPLIED,
									   STBIR_EDGE_CLAMP, USE_FILTER, STBIR_COLORSPACE_SRGB, nullptr);
		} else {
			stbir_resize_uint8_generic(mipData, pw, ph, 0, newData, w, h, 0, channelsPerPixel(format), -1,
									   STBIR_FLAG_ALPHA_PREMULTIPLIED, STBIR_EDGE_CLAMP, USE_FILTER,
									   STBIR_COLORSPACE_SRGB, nullptr);
		}

		if (mipData != data) free(mipData);
		mipData = newData;
	}
	if (mipData != data) free(mipData);
}

} // namespace wb
