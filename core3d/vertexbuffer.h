#pragma once

#include "formats.h"

namespace wb {

class VertexBuffer : public Shared {
public:
	uint const length;
	VertexFormat const format;

protected:
	VertexBuffer(uint length, VertexFormat format) : length(length), format(std::move(format)) {
	}
};

} // namespace wb
