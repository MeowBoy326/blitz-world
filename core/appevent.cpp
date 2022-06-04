#include "appevent.h"

#include <condition_variable>
#include <deque>
#include <mutex>

namespace wb {

namespace appevent {
Signal<> startup;
} // namespace appevent

namespace {

struct Event {
	EventFunc func;
	void* context;
};

std::deque<Event> g_deque;

std::mutex g_dequeMutex;
std::condition_variable g_dequeCondVar;

} // namespace

// Post event from an external thread to main thread
void postAsyncEvent(Function<void()> func, void* context) {
	{
		std::lock_guard<std::mutex> lock(g_dequeMutex);

		g_deque.push_back({func, context});
	}
	g_dequeCondVar.notify_one();
}

// Discard events with context
void discardAsyncEvents(void* context) {
	{
		std::lock_guard<std::mutex> lock(g_dequeMutex);

		for (auto& e : g_deque) {

			if (e.context == context) e.func = {};
		}
	}
}

void pollAsyncEvents() {

	uint n;
	{
		std::lock_guard<std::mutex> lock(g_dequeMutex);
		n = g_deque.size();
	}
	while (n--) {
		Event ev;
		{
			std::lock_guard<std::mutex> lock(g_dequeMutex);
			ev = g_deque.front();
			g_deque.pop_front();
		}
		if (ev.func) ev.func();
	}
}

void waitAsyncEvents() {

	uint n;
	{
		std::unique_lock<std::mutex> lock(g_dequeMutex);
		g_dequeCondVar.wait(lock, [] { return !g_deque.empty(); });
		n = g_deque.size();
	}
	while (n--) {
		Event ev;
		{
			std::lock_guard<std::mutex> lock(g_dequeMutex);
			ev = g_deque.front();
			g_deque.pop_front();
		}
		if (ev.func) ev.func();
	}
}

} // namespace wb
