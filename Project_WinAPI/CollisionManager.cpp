#include "Stdafx.h"
#include "SingletonBase.h"
#include "CollisionManager.h"

HRESULT CollisionManager::Init(void)
{
	return S_OK;
}

void CollisionManager::Update(void)
{
}

void CollisionManager::Release(void)
{
}

DirectionType CollisionManager::CheckCollision(tagCollider lColl, tagCollider rColl)
{
	if (lColl.rect.left < rColl.rect.right && lColl.rect.bottom > rColl.rect.top &&
		lColl.rect.top < rColl.rect.bottom && lColl.rect.right > rColl.rect.right) {
		return DirectionType::LEFT;
	}
	if (lColl.rect.right > rColl.rect.left && lColl.rect.bottom > rColl.rect.top &&
		lColl.rect.top < rColl.rect.bottom && lColl.rect.left < rColl.rect.left) {
		return DirectionType::RIGHT;
	}
	if (lColl.rect.left < rColl.rect.right && lColl.rect.top < rColl.rect.bottom &&
		lColl.rect.bottom > rColl.rect.bottom && lColl.rect.right > rColl.rect.left) {
		return DirectionType::UP;
	}
	if (lColl.rect.left < rColl.rect.right && lColl.rect.bottom >= rColl.rect.top &&
		lColl.rect.right > rColl.rect.left) {
		return DirectionType::DOWN;
	}
	return DirectionType::NONE;
}
