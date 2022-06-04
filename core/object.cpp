#include "object.h"

namespace wb {

Object::~Object() {
	deleted.emit();
}

} // namespace wb
