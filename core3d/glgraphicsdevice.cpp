#include "glgraphicsdevice.h"

#include "glutils.h"

namespace wb {

Shader* GLGraphicsDevice::createShader(CString source) {

	verify(!glGetError());

	auto createShader = [](GLenum type, const char* source) -> GLuint {
		while (*source && *source <= ' ') ++source;

		GLuint shader = glCreateShader(type);
		if (!shader) panic("glCreateShader failed");

		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Check compile status
		GLint status = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			GLint length = 1;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetShaderInfoLog(shader, length, nullptr, log);
			log[length - 1] = 0;
			debug() << "Compile shader failed:";
			auto lines = splitString(source, "\n");
			for (size_t i = 0; i < lines.size(); ++i) { debug() << i + 1 << " : " << lines[i]; }
			debug() << log;
			delete[] log;
			panic("OOPS");
		}

		return shader;
	};

	size_t i0 = source.find("\n//@vertex");
	verify(i0 != String::npos);

	size_t i1 = source.find("\n//@fragment", i0);
	verify(i1 != String::npos);

	String vsource = source.substr(0, i1);
	String fsource = source.substr(0, i0) + source.substr(i1);

	GLuint vshader = createShader(GL_VERTEX_SHADER, vsource.c_str());
	GLuint fshader = createShader(GL_FRAGMENT_SHADER, fsource.c_str());

	GLuint program = glCreateProgram();
	if (!program) panic("glCreateProgram failed");

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);

	glLinkProgram(program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	// Check link status
	GLint status = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		GLint length = 10;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetProgramInfoLog(program, length, nullptr, log);
		log[length - 1] = 0;
		debug() << "Link shader program failed:" << length;
		debug() << log;
		panic("OOPS");
	}

	verify(!glGetError());

	return new GLShader(program);
}

Texture* GLGraphicsDevice::createTexture(uint width, uint height, PixelFormat format, FilterFlags flags,
										 const void* data) {

	verify(!glGetError());

	GLenum glTarget = GL_TEXTURE_2D;

	GLuint glTexture;
	glGenTextures(1, &glTexture);
	glBindTexture(glTarget, glTexture);

	float aniso = 0.0f;
	if (GLEW_EXT_texture_filter_anisotropic) { glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso); }

	if ((flags & FilterFlags::mipmap) == FilterFlags::mipmap) {
		glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		if (aniso) glTexParameterf(glTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
	} else if ((flags & FilterFlags::linear) == FilterFlags::linear) {
		glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	if ((flags & FilterFlags::clampS) == FilterFlags::clampS) {
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	} else {
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}
	if ((flags & FilterFlags::clampT) == FilterFlags::clampT) {
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else {
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	setGLTextureData(width, height, format, flags, data);

	glBindTexture(glTarget, 0);

	verify(!glGetError());

	return new GLTexture(width, height, format, flags, glTexture);
}

FrameBuffer* GLGraphicsDevice::createFrameBuffer(Texture* colorTexture, Texture* depthTexture) {

	verify(!glGetError());

	auto glColorTexture = static_cast<GLTexture*>(colorTexture);
	auto glDepthTexture = static_cast<GLTexture*>(depthTexture);

	GLuint glFramebuffer;
	glGenFramebuffers(1, &glFramebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, glFramebuffer);

	if (glColorTexture) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, glColorTexture->glTexture, 0);
	}
	if (glDepthTexture) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, glDepthTexture->glTexture, 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	verify(!glGetError());

	return new GLFrameBuffer(colorTexture, depthTexture, glFramebuffer);
}

VertexBuffer* GLGraphicsDevice::createVertexBuffer(uint length, VertexFormat format, const void* data) {

	verify(!glGetError());

	GLenum glAttribTypes[] = {GL_NONE,	GL_FLOAT, GL_FLOAT,			GL_FLOAT,
							  GL_FLOAT, GL_BYTE,  GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE};

	Vector<GLAttribPtr> attribPtrs;
	uint stride = bytesPerVertex(format);
	char* pointer = 0;
	for (auto attrib : format) {
		auto size = channelsPerAttrib(attrib);
		auto type = glAttribTypes[int(attrib)];
		attribPtrs.push_back(GLAttribPtr{(GLint)size, type, false, (GLsizei)stride, pointer});
		pointer += bytesPerAttrib(attrib);
	}

	GLuint glBuffer;
	glGenBuffers(1, &glBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
	glBufferData(GL_ARRAY_BUFFER, length * stride, data,  data ? GL_STATIC_DRAW : GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	verify(!glGetError());

	return new GLVertexBuffer(length, std::move(format), glBuffer, std::move(attribPtrs));
}

IndexBuffer* GLGraphicsDevice::createIndexBuffer(uint length, IndexFormat format, const void* data) {

	verify(!glGetError());

	size_t bpi = (format == IndexFormat::uint32 ? 4 : 2);

	GLuint glBuffer;
	glGenBuffers(1, &glBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * bytesPerIndex(format), data, data ? GL_STATIC_DRAW : GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	verify(!glGetError());

	return new GLIndexBuffer(length,format,glBuffer);
}

} // namespace wb
