#pragma once
#include "Collider.h"

class CollisionManager : public SingletonBase <CollisionManager>
{
public:
	HRESULT Init(void);
	void Update(void);
	void Release(void);
public:
	DirectionType CheckCollision(tagCollider lColl, tagCollider rColl);

	CollisionManager() {}
	~CollisionManager() {}
};

