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

	template <class SourceTy> SharedPtr(SourceTy* ptr) : m_ptr(ptr) {
		retain(m_ptr);
	}

	template <class SourceTy> SharedPtr(const SharedPtr<SourceTy>& shared) : m_ptr(shared.m_ptr) {
		retain(m_ptr);
	}

	template <class SourceTy> SharedPtr(SharedPtr<SourceTy>&& shared) noexcept : m_ptr(shared.m_ptr) {
		shared.m_ptr = nullptr;
	}

	template <class SourceTy> SharedPtr& operator=(SourceTy* ptr) {
		retain(ptr);
		release(m_ptr);
		m_ptr = ptr;
		return *this;
	}

	template <class SourceTy> SharedPtr& operator=(const SharedPtr<SourceTy> shared) {
		retain(shared.m_ptr);
		release(m_ptr);
		m_ptr = shared.m_ptr;
		return *this;
	}

	template <class SourceTy> SharedPtr& operator=(SharedPtr<SourceTy>&& shared) noexcept {
		if (m_ptr == shared.m_ptr) return *this;
		release(m_ptr);
		m_ptr = shared.m_ptr;
		shared.m_ptr = nullptr;
		return *this;
	}

	template <class SourceTy> bool operator==(SourceTy* ptr) const {
		return m_ptr == ptr;
	}

	template <class SourceTy> bool operator==(const SharedPtr& shared) const {
		return m_ptr == shared.m_ptr;
	}

	template <class SourceTy> friend bool operator==(SourceTy* ptr, const SharedPtr& shared) {
		return ptr == shared.m_ptr;
	}

	template <class SourceTy> bool operator!=(SourceTy* ptr) const {
		return m_ptr != ptr;
	}

	template <class SourceTy> bool operator!=(const SharedPtr& shared) const {
		return m_ptr != shared.m_ptr;
	}

	template <class SourceTy> friend bool operator!=(SourceTy* ptr, const SharedPtr& shared) {
		return ptr != shared.m_ptr;
	}

	template <class SourceTy> bool operator<(SourceTy * ptr) const {
		return m_ptr < ptr;
	}

	template <class SourceTy> bool operator<(const SharedPtr& shared) const {
		return m_ptr < shared.m_ptr;
	}

	template <class SourceTy> friend bool operator<(SourceTy * ptr, const SharedPtr& shared) {
		return ptr < shared.m_ptr;
	}

	explicit operator bool() const {
		return m_ptr != nullptr;
	}

	explicit operator SharedTy*() const {
		return m_ptr;
	}

	SharedTy* operator->() const {
		return m_ptr;
	}

	SharedTy& operator*() const {
		return *m_ptr;
	}

	SharedTy* value() const {
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

} // namespace wb
