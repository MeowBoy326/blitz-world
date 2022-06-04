#pragma once

#include "shared.h"

namespace wb {

//! \brief The SharedPtr template class
//!
//! Used to keep Shared instances alive.
//!
//! You should only use SharedPtr when storing shared objects on the heap (ie: in globals or fields).
//!
//! Otherwise, shared objects should just be passed and returned as raw pointers and everything should just work?
//!
template <class SharedTy> class SharedPtr {
public:
	SharedPtr() = default;

	~SharedPtr() {
		release(m_ptr);
	}

	SharedPtr(SharedTy* ptr) : m_ptr(ptr) {
		retain(m_ptr);
	}

	SharedPtr(const SharedPtr& sharedPtr) : m_ptr(sharedPtr.m_ptr) {
		retain(m_ptr);
	}

	SharedPtr(SharedPtr&& sharedPtr) : m_ptr(sharedPtr.m_ptr) {
		sharedPtr.m_ptr = nullptr;
	}

	SharedPtr& operator=(SharedTy* ptr) {
		retain(ptr);
		release(m_ptr);
		m_ptr = ptr;
		return *this;
	}

	SharedPtr& operator=(const SharedPtr& sharedPtr) {
		retain(sharedPtr.m_ptr);
		release(m_ptr);
		m_ptr = sharedPtr.m_ptr;
		return *this;
	}

	SharedPtr& operator=(SharedPtr&& sharedPtr) {
		if (m_ptr == sharedPtr.m_ptr) return *this;
		release(m_ptr);
		m_ptr = sharedPtr.m_ptr;
		sharedPtr.m_ptr = nullptr;
		return *this;
	}

	explicit operator bool() const {
		return m_ptr != nullptr;
	}

	bool operator==(SharedTy* ptr) const {
		return m_ptr == ptr;
	}

	bool operator!=(SharedTy* ptr) const {
		return !operator==(ptr);
	}

	bool operator<(SharedTy* ptr) const {
		return m_ptr < ptr;
	}

	operator SharedTy*() const {
		return m_ptr;
	}

	SharedTy* operator->() const {
		return m_ptr;
	}

	SharedTy& operator*() const {
		return *m_ptr;
	}

	SharedTy* get() const {
		return m_ptr;
	}

private:
	SharedTy* m_ptr = nullptr;

	static inline void retain(Shared* shared) {
		assert(!shared || shared->m_sharedRefs < 10000);

		if (shared) ++shared->m_sharedRefs;
	}

	static inline void release(Shared* shared) {
		assert(!shared || shared->m_sharedRefs > 0);

		if (!shared || --shared->m_sharedRefs) return;

		shared->m_sharedRefs = 1;
		SharedPtrPool::g_instance->m_sharedPtrs.push_back(shared);
	}
};

template <class SharedTy> SharedPtr<SharedTy> sharedPtr(SharedTy* ptr) {
	return ptr;
}

} // namespace wb
