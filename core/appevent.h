#pragma once

#include "function.h"
#include "signal.h"

namespace wb {

namespace appevent {
extern Signal<> startup;
} // namespace appevent

using EventFunc = Function<void()>;

// Called on an external thread to unblock app thread
void postAsyncEvent(EventFunc event, void* context = nullptr);

// Called on the app thread
void discardAsyncEvents(void* context);

// Called on the app thread
void pollAsyncEvents();

// Called on the app thread
void waitAsyncEvents();

} // namespace wb
