#pragma once

#include "imguiex.h"

#include <geom/geom.hh>
#include <imgui/imgui.hh>

// Include the GL headers
#define GLFW_INCLUDE_ES31 1
#define GLFW_INCLUDE_GLEXT 1
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace wb {

class Keyboard;
class Gamepad;

namespace settings {
extern BoolProperty showDebugLog;
extern BoolProperty showDebugInfo;
extern BoolProperty fullScreen;
extern BoolProperty vsyncEnabled;
} // namespace settings

namespace stats {
extern FloatProperty refreshRate;
extern UIntProperty FPS;
extern UIntProperty cpuIdle;
extern UIntProperty gpuIdle;
} // namespace stats

class GLWindow : public Object {
public:
	static constexpr uint maxGamepads = 4;

	Property<bool> keyEventsEnabled{true};

	Signal<uint, bool> gamepadConnectedChanged;

	Signal<Vec2i> sizeChanged;
	Signal<> shouldClose;
	Signal<> gotFocus;
	Signal<> lostFocus;
	Signal<> updating;

	GLWindow(CString title, uint width, uint height);
	~GLWindow();

	CVec2i position() const {
		return m_position;
	}

	CVec2i size() const {
		return m_size;
	}

	bool closed() const {
		return m_glfwWindow == nullptr;
	}

	bool focus() const {
		return m_focus;
	}

	Keyboard* keyboard() const {
		return m_keyboard;
	}

	Gamepad* gamepad(uint index) const {
		assert(index < maxGamepads);
		return m_gamepads[index];
	}

	void run(Function<void()> funFunc);

	void close();

private:
	static GLWindow* getWindow(GLFWwindow* glfwWindow);

	GLFWwindow* m_glfwWindow;

	Keyboard* m_keyboard;
	Gamepad* m_gamepads[maxGamepads];

	bool m_focus = true;
	Vec2i m_position;
	Vec2i m_size;

	Vec2i m_restorePosition;
	Vec2i m_restoreSize;

	double m_idleTime;
	double m_fpsTime;
	uint m_fps;

	Function<void()> m_runFunc;

	ImGuiEx::ImGuiLog m_log;

	void drawDebugLog();
	void drawDebugInfo();
	void updateFPS();
	void updateIdleStats();
	void updateEvents();
	void swapBuffers();
	void singleStep();
	void clearHitKeys();
};

} // namespace wb
