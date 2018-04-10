#pragma once

#include "ecsx/CompDenseStorage.h"
#include "ecsx/CompSparseStorage.h"

#include <guard/check.h>

namespace ecsx
{
namespace detail
{

template <typename T>
inline bool ComponentPool::HasComponent(Entity e) const
{
	return e.u.index >= 0 && e.u.index < m_masks.size() 
		&& m_masks[e.u.index][GetComponentTypeID<T>()];
}

template <typename T, typename... Args>
inline T& ComponentPool::AddComponent(Entity e, Args&&... args)
{
	GD_ASSERT(!HasComponent<T>(e), "has comp");

	auto idx = GetComponentTypeID<T>();

	m_masks.resize(std::max(e.u.index + 1, m_masks.size()));
	m_masks[e.u.index].set(idx);

	auto storage = m_storage[idx];
	T comp(std::forward<Args>(args)...);
	storage->Add(e.u.index, &comp);
	return *static_cast<T*>(storage->Get(e.u.index));
}

template <typename T>
T& ComponentPool::GetComponent(Entity e) const
{
	GD_ASSERT(HasComponent<T>(e), "no component");
	return *reinterpret_cast<T*>(m_storage[GetComponentTypeID<T>()]->Get(e.u.index));
}

template <typename T>
inline void ComponentPool::SetStorage(CompStorageType type)
{
	int idx = GetComponentTypeID<T>();
	if (m_storage[idx]) {
		delete m_storage[idx];
	}

	IComponentsStorage* storage = nullptr;
	switch (type)
	{
	case COMP_STORAGE_DENSE:
		storage = new CompDenseStorage<T>();
		break;
	case COMP_STORAGE_SPARSE:
		storage = new CompSparseStorage<T>();
		break;
	}
	m_storage[idx] = storage;
}

}
}