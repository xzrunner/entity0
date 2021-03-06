#include "entity0/EntityPool.h"

namespace e0
{
namespace detail
{

EntityPool::EntityPool()
	: m_next_id(0)
{
}

Entity EntityPool::Create()
{
	Entity e;
	if (m_freelist.empty())
	{
		e.index = m_next_id++;
		e.version = 1;
		m_versions.push_back(e.version);
	}
	else
	{
		e = m_freelist.back();
		m_freelist.pop_back();
	}
	return e;
}

void EntityPool::Destroy(Entity e)
{
	m_freelist.push_back(e);
}

}
}