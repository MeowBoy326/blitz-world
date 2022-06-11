#pragma once

#include "framebuffer.h"
#include "shader.h"
#include "texture.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

namespace wb {

class GraphicsDevice {
public:
	virtual Shader* createShader(CString source) = 0;
	virtual Texture* createTexture(uint width, uint height, PixelFormat format, FilterFlags flags,
								   const void* data) = 0;
	virtual FrameBuffer* createFrameBuffer(Texture* colorTexture, Texture* depthTexture) = 0;

	virtual VertexBuffer* createVertexBuffer(uint length, VertexFormat format, const void* data) = 0;

	virtual IndexBuffer* createIndexBuffer(uint length, IndexFormat format, const void* data) = 0;

	friend void createGraphicsDevice();

	friend GraphicsDevice* graphicsDevice() {
		return g_device;
	}

protected:
	static GraphicsDevice* g_device;
};

} // namespace wb
