#pragma once

#include "function.h"
#include "object.h"
#include "signal.h"

namespace wb {

template <class ValueTy> class Property;

using BoolProperty = Property<bool>;
using IntProperty = Property<int>;
using UIntProperty = Property<uint>;
using FloatProperty = Property<float>;
using StringProperty = Property<String>;

template <class ValueTy> class Property : public Object {
public:
	using CValueTy = const ValueTy&;

	Signal<CValueTy, CValueTy> valueChanging; //(newValue, oldValue)
	Signal<CValueTy> valueChanged;			  //(newValue)

	Property() = default;
	explicit Property(CValueTy value) : m_value(value) {
	}
	//	Property(const Property& property) : m_value(property.m_value) {
	//	}
	Property(const Property&& property) = delete;

	void setValue(CValueTy newValue) {
		if (newValue == m_value) return;
		valueChanging.emit(newValue, m_value);
		m_value = newValue;
		valueChanged.emit(newValue);
	}

	CValueTy value() const {
		return m_value;
	}

	bool operator==(CValueTy value) const {
		return m_value == value;
	}

	bool operator!=(CValueTy value) const {
		return !operator==(value);
	}

	Property& operator=(CValueTy newValue) {
		setValue(newValue);
		return *this;
	}

	//	Property& operator=(const Property& property) {
	//		setValue(property.value());
	//		return *this;
	//	}

	Property& operator=(Property&&) = delete;

	operator CValueTy() const {
		return m_value;
	}

	auto operator->() {
		return m_value.ValueTy::operator->();
	}

	auto operator->() const {
		return m_value.ValueTy::operator->();
	}

	template <class RetTy> operator RetTy*() const {
		return m_value.ValueTy::operator->();
	}

	friend std::ostream& operator<<(std::ostream& str, const Property& property) {
		return str << property.m_value;
	}

private:
	ValueTy m_value = {};
};

} // namespace wb
