#pragma once

#include <string>
#include "ImageCodex.h"
#include "Surface.h"

class Actor
{
public:
	Actor() {}
	virtual ~Actor() {}
	Actor( const Actor& ) = default;
	Actor( Actor&& ) = default;
	Actor& operator=( const Actor& ) = default;
	Actor& operator=( Actor&& ) noexcept = default;
	virtual void Update( float dt, class Scene& scene ) = 0;
	virtual void Draw( HDC hdc ) = 0;
	void SetDestroy()
	{
		shouldDestroy = true;
	}
	bool ShouldDestroy() const
	{
		return shouldDestroy;
	}
protected:
	Surface surface;
	bool shouldDestroy = false;
};