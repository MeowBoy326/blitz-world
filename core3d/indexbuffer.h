#pragma once

#include "formats.h"

namespace wb {

class IndexBuffer : public Shared {
public:
	uint const length;
	IndexFormat const format;

protected:
	IndexBuffer(uint length, IndexFormat format) : length(length), format(format) {
	}
};

} // namespace wb
