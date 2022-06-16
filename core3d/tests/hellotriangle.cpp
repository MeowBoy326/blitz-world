
#include "glwindow/glwindow.hh"

#include <core3d/core3d.hh>

using namespace wb;

constexpr auto shaderSource = R"(

//@vertex

layout(location=0) in vec2 aPosition;
layout(location=1) in vec4 aColor;

out vec4 color;

void main() {

	gl_Position = vec4(aPosition, 0.0, 1.0);
	color=aColor;
}

//@fragment

in vec4 color;

struct SceneParams {
	vec4 clearColor;
};

layout (std140) uniform sceneParams {
	SceneParams scene;
};

out vec4 fragColor;

void main() {

	fragColor = color * scene.clearColor;
}

)";

struct SceneParams {
	Vec4f clearColor;
};

struct Vertex {
	Vec2f position;
	Vec4f color;
};

int main() {

	uint width = 1280;
	uint height = 720;

	auto window = new GLWindow("Skirmish 2022!", width, height);

#ifndef USE_OPENGLES
	auto debugFunc = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
						const void* userParam) { debug() << "OpenGL Debug:" << message; };
	glDebugMessageCallback(debugFunc, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
#endif

	auto device = new GLGraphicsDevice();

	auto context = device->createGraphicsContext();

	Vertex vertices[] = {{{0, 1}, {1, 0, 0, 1}}, {{1, -1}, {0, 1, 0, 1}}, {{-1, -1}, {0, 0, 1, 1}}};
	auto vbuffer = device->createVertexBuffer(3, {AttribFormat::float2, AttribFormat::float4}, vertices);

	SceneParams sceneParams{1};
	auto ubuffer = device->createUniformBuffer(sizeof(SceneParams), &sceneParams);

	auto shader = device->createShader(shaderSource);

	context->setVertexBuffer(vbuffer);
	context->setUniformBuffer("sceneParams", ubuffer);
	context->setSimpleUniform("color", Any(Vec4f(1, .5f, .25, 1)));
	context->setShader(shader);

	window->run([device, context, shader] {
		context->clear(Vec4f(0, 0, 1, 1));

		context->drawGeometry(3, 0, 3, 1);
	});
}
