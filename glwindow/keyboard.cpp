#include "keyboard.h"

#include <GLFW/glfw3.h>

namespace wb {

// ***** Keyboard *****

Keyboard::Keyboard() : UIDevice(512) {
}

void Keyboard::sendKeyEvent(int key, int scancode, int action, int mods) {

	if (uint(key) >= maxButtons() || (action != GLFW_PRESS && action != GLFW_RELEASE)) return;

	setButtonDown(key, action == GLFW_PRESS);
}

} // namespace wb
