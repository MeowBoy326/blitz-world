#pragma once

#include "texture.h"

namespace wb {

class FrameBuffer : public Shared {
public:
	SharedPtr<Texture> const colorTexture;
	SharedPtr<Texture> const depthTexture;

protected:
	FrameBuffer(Texture* colorTexture, Texture* depthTexture) : colorTexture(colorTexture), depthTexture(depthTexture) {
	}
};

}; // namespace wb
