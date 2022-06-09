#pragma once

#ifdef USE_OPENGLES
    #include <GLES3/gl31.h>
#else
    #ifdef WIN32
        #include <GL/glew.h>
    #else
        #include <GL/gl.h>
    #endif
#endif

namespace wb {
    //  Needs to be a current opengl context when this is called
    void initOpenGL();
}

