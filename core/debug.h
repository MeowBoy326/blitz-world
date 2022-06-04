#pragma once

#include "function.h"
#include "std.h"

#include <cstdio>
#include <sstream>

namespace wb {

constexpr float debugZeroEpsilon = .0001f;

using DebugOutputFunc = Function<void(CString)>;

extern thread_local DebugOutputFunc debugOutputFunc;

String debugTimestamp();
void defaultDebugOutputFunc(CString);

class DebugStream {
	struct Rep {
		std::stringstream buf;
		bool space = false;
		~Rep() {
			debugOutputFunc(buf.str());
		}
	};
	Rep* rep = new Rep;

	template <class T> friend DebugStream&& operator<<(DebugStream&& dbgstream, const T& value) {
		Rep* rep = dbgstream.rep;
		if (rep->space) rep->buf << ' ';
		rep->space = true;
		rep->buf << value;
		return std::move(dbgstream);
	}

public:
	DebugStream() = default;
	~DebugStream() {
		delete rep;
	}

	DebugStream(const DebugStream&) = delete;
	DebugStream(DebugStream&& rhs) : rep(rhs.rep) {
		rhs.rep = nullptr;
	}

	DebugStream& operator=(const DebugStream& rhs) = delete;
	DebugStream& operator=(DebugStream&& rhs) {
		rep = rhs.rep;
		rhs.rep = nullptr;
		return *this;
	}
};

inline DebugStream debug() {
	return DebugStream();
}

inline bool isZero(float n, float epsilon = debugZeroEpsilon) {
	if (std::abs(n) <= epsilon) return true;
	debug() << "### isZero: value=" << n;
	return false;
}

inline bool isUnit(float n, float epsilon = debugZeroEpsilon) {
	if (std::abs(std::abs(n) - 1) <= epsilon) return true;
	debug() << "### isUnit: value=" << n;
	return false;
}

} // namespace wb
