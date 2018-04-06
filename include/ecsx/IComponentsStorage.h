#pragma once

#include "ecsx/Config.h"

namespace ecsx
{
namespace detail
{

class IComponentsStorage
{
public:
	virtual void Add(const ID_TYPE& idx, void* data) = 0;
	virtual void* Get(const ID_TYPE& idx) = 0;
	virtual void Clear() = 0;

}; // IComponentsStorage

}
}