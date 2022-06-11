#pragma once

#include "formats.h"

#include <opengl/opengl.hh>

namespace wb {

struct GLPixelFormat {
	GLenum internalFormat;
	GLenum format;
	GLenum type;
};

GLPixelFormat glPixelFormats[] = {{GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE},
								  {GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE},
								  {GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
								  {GL_RGB, GL_RGB, GL_UNSIGNED_BYTE},
								  {GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE},
								  {GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE},
								  {GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE},
								  {GL_R32F, GL_RED, GL_FLOAT},
								  {GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT},
								  {GL_RGBA16F, GL_RGBA, GL_FLOAT}};

void setGLTextureData(uint width, uint height, PixelFormat format, FilterFlags flags, const void* data);

} // namespace wb
