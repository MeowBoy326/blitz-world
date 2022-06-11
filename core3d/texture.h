#pragma once

#include "formats.h"

namespace wb {

class Texture : public Shared {
public:
	uint const width;
	uint const height;
	PixelFormat const texelFormat;
	FilterFlags const filterFlags;

protected:
	Texture(uint width, uint height, PixelFormat format, FilterFlags flags)
		: width(width), height(height), texelFormat(format), filterFlags(flags) {
	}
};

} // namespace wb
