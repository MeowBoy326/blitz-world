#pragma once

#include "types.h"

namespace wb {

class GraphicsDevice;

// ***** GraphicsResource ******

class GraphicsResource : public Shared {
public:
	SharedPtr<GraphicsDevice> const graphicsDevice;

protected:
	GraphicsResource(GraphicsDevice* device) : graphicsDevice(device) {
	}
};

// ***** Texture *****

class Texture : public GraphicsResource {
public:
	uint const width;
	uint const height;
	PixelFormat const texelFormat;
	FilterFlags const filterFlags;

protected:
	Texture(GraphicsDevice* device, uint width, uint height, PixelFormat format, FilterFlags flags)
		: GraphicsResource(device), width(width), height(height), texelFormat(format), filterFlags(flags) {
	}
};

// ***** UniformBuffer *****

class UniformBuffer : public GraphicsResource {
public:
	uint const size;

protected:
	UniformBuffer(GraphicsDevice* device, uint size) : GraphicsResource(device), size(size) {
	}
};

// ***** VertexBuffer *****

class VertexBuffer : public GraphicsResource {
public:
	uint const length;
	VertexFormat const format;

protected:
	VertexBuffer(GraphicsDevice* device, uint length, VertexFormat format)
		: GraphicsResource(device), length(length), format(std::move(format)) {
	}
};

// ***** IndexBuffer *****

class IndexBuffer : public GraphicsResource {
public:
	uint const length;
	IndexFormat const format;

protected:
	IndexBuffer(GraphicsDevice* device, uint length, IndexFormat format)
		: GraphicsResource(device), length(length), format(format) {
	}
};

// ***** FrameBuffer *****

class FrameBuffer : public GraphicsResource {
public:
	SharedPtr<Texture> const colorTexture;
	SharedPtr<Texture> const depthTexture;

protected:
	FrameBuffer(GraphicsDevice* device, Texture* colorTexture, Texture* depthTexture)
		: GraphicsResource(device), colorTexture(colorTexture), depthTexture(depthTexture) {
	}
};

// ***** Shader *****

class Shader : public GraphicsResource {
public:
	String const source;

protected:
	Shader(GraphicsDevice* device, String source) : GraphicsResource(device), source(std::move(source)) {
	}
};

// ***** GraphicsContext *****

class GraphicsContext : public GraphicsResource {
public:
	virtual void setViewport(CRecti viewport) = 0;
	virtual void setDepthMode(DepthMode mode) = 0;
	virtual void setBlendMode(BlendMode mode) = 0;
	virtual void setCullMode(CullMode mode) = 0;

	virtual void setFrameBuffer(FrameBuffer* frameBuffer) = 0;
	virtual void setVertexBuffer(VertexBuffer* buffer) = 0;
	virtual void setIndexBuffer(IndexBuffer* buffer) = 0;

	virtual void setUniformBuffer(CString name, UniformBuffer* buffer) = 0;
	virtual void setTextureUniform(CString name, Texture* texture) = 0;
	virtual void setSimpleUniform(CString name, CAny any) = 0;
	virtual void setShader(Shader* shader) = 0;

	virtual void clear(CVec4f color) = 0;
	virtual void drawIndexedGeometry(uint order, uint firstVertex, uint numVertices, uint numInstances) = 0;
	virtual void drawGeometry(uint order, uint firstVertex, uint numVertices, uint numInstances) = 0;

protected:
	explicit GraphicsContext(GraphicsDevice* device) : GraphicsResource(device) {
	}
};

// ***** GraphicsDevice *****

class GraphicsDevice : public Shared {
public:
	virtual Texture* createTexture(uint width, uint height, PixelFormat format, FilterFlags flags,
								   const void* data) = 0;
	virtual UniformBuffer* createUniformBuffer(uint size, const void* data) = 0;
	virtual VertexBuffer* createVertexBuffer(uint length, VertexFormat format, const void* data) = 0;
	virtual IndexBuffer* createIndexBuffer(uint length, IndexFormat format, const void* data) = 0;
	virtual FrameBuffer* createFrameBuffer(Texture* colorTexture, Texture* depthTexture) = 0;
	virtual Shader* createShader(CString source) = 0;
	virtual GraphicsContext* createGraphicsContext() = 0;
};

} // namespace wb
