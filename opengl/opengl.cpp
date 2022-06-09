#include "opengl.hh"

namespace wb {

void initOpenGL() {
#ifdef USE_OPENGLES
#else
#ifdef WIN32
    glewInit();
#else
#endif
#endif
}

}