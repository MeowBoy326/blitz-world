#pragma once

#include "std.h"

namespace wb {

using bitmask = uint32_t;

#define BITMASK_OP                                                                                                     \
	template <class EnumTy,                                                                                            \
			  class = std::enable_if<std::is_same<typename std::underlying_type<EnumTy>::type, bitmask>::value>>

BITMASK_OP EnumTy operator&(EnumTy x, EnumTy y) {
	return EnumTy(int(x) & int(y));
}
BITMASK_OP EnumTy operator|(EnumTy x, EnumTy y) {
	return EnumTy(int(x) | int(y));
}
BITMASK_OP EnumTy operator^(EnumTy x, EnumTy y) {
	return EnumTy(int(x) ^ int(y));
}
BITMASK_OP EnumTy& operator&=(EnumTy& x, EnumTy y) {
	return x = EnumTy(x & y);
}
BITMASK_OP EnumTy& operator|=(EnumTy& x, EnumTy y) {
	return x = EnumTy(x | y);
}
BITMASK_OP EnumTy& operator^=(EnumTy& x, EnumTy y) {
	return x = EnumTy(x ^ y);
}
BITMASK_OP EnumTy operator~(EnumTy x) {
	return EnumTy(~int(x));
}

} // namespace wb
