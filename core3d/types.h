#pragma once

#include <geom/geom.hh>

namespace wb {

enum struct BlendMode { disable, alpha, additive, multiply };

enum struct DepthMode { disable, enable, compare };

enum struct CullMode { disable, front, back, all };

enum struct PixelFormat {
	alpha8,
	intensity8,
	intensityAlpha16,
	rgb24,
	srgb24,
	rgba32,
	srgba32,
	r32f,
	depth32f,
	rgba64f
};

enum struct FilterFlags {
	none = 0,
	clampS = 1,
	clampT = 2,
	linear = 4,
	mipmap = 8, // also implies linear
	clampST = 3,
};

enum struct AttribFormat { none, float1, float2, float3, float4, sbyte4, ubyte4, ubyte2 };

using VertexFormat = Vector<AttribFormat>;
using CVertexFormat = const VertexFormat&;

enum struct IndexFormat { uint8, uint16, uint32 };

inline uint channelsPerPixel(PixelFormat format) {
	static constexpr uint r[] = {1, 1, 2, 3, 3, 4, 4, 1, 1, 4};
	assert(uint(format) < std::size(r));
	return r[uint(format)];
}

inline uint bytesPerChannel(PixelFormat format) {
	static constexpr uint r[] = {1, 1, 1, 1, 1, 1, 1, 4, 4, 2};
	assert(uint(format) < std::size(r));
	return r[uint(format)];
}

inline uint bytesPerPixel(PixelFormat format) {
	static constexpr uint r[] = {1, 1, 2, 3, 3, 4, 4, 4, 4, 8};
	assert(uint(format) < std::size(r));
	return r[uint(format)];
}

inline uint channelsPerAttrib(AttribFormat format) {
	static constexpr uint r[] = {0, 1, 2, 3, 4, 4, 4, 2};
	assert(uint(format) < std::size(r));
	return r[uint(format)];
}

inline uint bytesPerAttrib(AttribFormat format) {
	static constexpr uint r[] = {0, 4, 8, 12, 16, 4, 4, 2};
	assert(uint(format) < std::size(r));
	return r[uint(format)];
}

inline uint bytesPerVertex(CVertexFormat format) {
	uint r = 0;
	for (auto attrib : format) r += bytesPerAttrib(attrib);
	return r;
}

inline uint bytesPerIndex(IndexFormat format) {
	static constexpr uint r[] = {1, 2, 4};
	return r[int(format)];
}

} // namespace wb
