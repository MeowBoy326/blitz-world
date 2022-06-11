#pragma once

#include "graphicsdevice.h"

#include <opengl/opengl.hh>

namespace wb {

struct GLAttribPtr {
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;
};

class GLGraphicsDevice;

class GLShader : public Shader {
public:
	GLuint glProgram;

	~GLShader() override {
		glDeleteProgram(glProgram);
	}

protected:
	friend class GLGraphicsDevice;

	GLShader(GLuint glProgram) : glProgram(glProgram) {
	}
};

class GLTexture : public Texture {
public:
	GLuint glTexture;

	~GLTexture() override {
		glDeleteTextures(1, &glTexture);
	}

protected:
	friend class GLGraphicsDevice;

	GLTexture(uint width, uint height, PixelFormat format, FilterFlags flags, GLuint glTexture)
		: Texture(width, height, format, flags), glTexture(glTexture) {
	}
};

class GLFrameBuffer : public FrameBuffer {
public:
	GLuint glFramebuffer;

	~GLFrameBuffer() override {
		glDeleteFramebuffers(1, &glFramebuffer);
	}

protected:
	friend class GLGraphicsDevice;

	GLFrameBuffer(Texture* colorTexture, Texture* depthTexture, GLuint glFramebuffer)
		: FrameBuffer(colorTexture, depthTexture), glFramebuffer(glFramebuffer) {
	}
};

class GLVertexBuffer : public VertexBuffer {
public:
	GLuint const glBuffer;
	Vector<GLAttribPtr> const attribPtrs;

	~GLVertexBuffer() override {
		glDeleteBuffers(1, &glBuffer);
	}

protected:
	friend class GLGraphicsDevice;

	GLVertexBuffer(uint length, VertexFormat format, GLuint glBuffer, Vector<GLAttribPtr> attribPtrs)
		: VertexBuffer(length, std::move(format)), glBuffer(glBuffer), attribPtrs(std::move(attribPtrs)) {
	}
};

class GLIndexBuffer : public IndexBuffer {
public:
	GLuint const glBuffer;

	~GLIndexBuffer() override {
		glDeleteBuffers(1, &glBuffer);
	}

protected:
	friend class GLGraphicsDevice;

	GLIndexBuffer(uint length, IndexFormat format, GLuint glBuffer) : IndexBuffer(length, format), glBuffer(glBuffer) {
	}
};

class GLGraphicsDevice : public GraphicsDevice {
public:
	Shader* createShader(CString source) override;
	Texture* createTexture(uint width, uint height, PixelFormat format, FilterFlags flags, const void* data) override;
	FrameBuffer* createFrameBuffer(Texture* colorTexture, Texture* depthTexture) override;
	VertexBuffer* createVertexBuffer(uint length, VertexFormat format, const void* data) override;
	IndexBuffer* createIndexBuffer(uint length, IndexFormat format, const void* data) override;

	// OpenGL extensions
	Texture* createGLTextureWrapper(uint width, uint height, PixelFormat format, FilterFlags flags, GLuint glTexture);
};

} // namespace wb
