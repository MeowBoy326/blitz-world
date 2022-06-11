#include "glgraphicsdevice.h"

namespace wb {

GraphicsDevice* GraphicsDevice::g_device;

void createGraphicsDevice() {
	assert(!GraphicsDevice::g_device);
	GraphicsDevice::g_device = new GLGraphicsDevice();
}

} // namespace wb
