
#include "glwindow/glwindow.h"

using namespace wb;

extern "C" const char* __asan_default_options() {
	return "abort_on_error=1:detect_leaks=0";
}

int main() {

	uint width = 1280;
	uint height = 720;

	debug() << "### Hello world!";

	auto window = new GLWindow("Skirmish 2022!", width, height);

	window->shouldClose.connect(window, &GLWindow::close);

	glClearColor(.25f, 0, 1, 1);

	window->run([] { glClear(GL_COLOR_BUFFER_BIT); });
}
