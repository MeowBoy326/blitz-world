#include "opengl.hh"

namespace wb {

void initOpenGL() {
#ifndef USE_OPENGLES
	glewInit();
#endif
}

} // namespace wb
