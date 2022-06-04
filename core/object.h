#ifndef WB_OBJECT_H
#define WB_OBJECT_H

#include "signal.h"
#include "std.h"

namespace wb {

class ObjectType {
public:
	String const name;
	ObjectType* const super;

	ObjectType(CString name, ObjectType* super) : name(name), super(super) {
	}

	bool extends(const ObjectType* thatType) const {
		for (auto thisType = this; thisType; thisType = thisType->super) {
			if (thisType == thatType) return true;
		}
		return false;
	}
};

#define WB_OBJECT_TYPE(name, super)                                                                                    \
	static inline ObjectType staticType{#name, &super::staticType};                                                    \
	ObjectType* dynamicType() const override {                                                                         \
		return &staticType;                                                                                            \
	}

class Object {
public:
	// Special case manual expansion of WB_OBJECT_TYPE for root object.
	static inline ObjectType staticType{"Object", nullptr};
	virtual ObjectType* dynamicType() const {
		return &staticType;
	}

	Signal<> deleted;

	Object() = default;
	virtual ~Object();

	bool instanceOf(ObjectType* type) const {
		return dynamicType()->extends(type);
	}

	template <class ObjTy> bool instanceOf() const {
		return dynamicType()->extends(&ObjTy::staticType);
	}

	template <class ObjTy> ObjTy* cast() {
		if (instanceOf<ObjTy>()) return static_cast<ObjTy*>(this);
		return nullptr;
	}

	template <class ObjTy> const ObjTy* cast() const {
		if (instanceOf<ObjTy>()) return static_cast<const ObjTy*>(this);
		return nullptr;
	}

private:
};

} // namespace wb

#include "signal_impl.inl"

#endif
