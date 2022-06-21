#include "Stdafx.h"
#include "Map.h"

HRESULT Map::Init()
{
	IMAGEMANAGER->addImage("boss_map", "Resources/Images/BackGround/boss_map.bmp", 1136 * 3, 240 * 3);

	_tPos = { 0, 0 };
	_tMapSize = { 1136 * 3, 240 * 3 };
	_tPivotPos = { 0, 0 };

	_cColl.SetAddCollider
	(
		ObjectType::MAP,
		ColliderType::BLOCK,
		{ 0, 240 * 3 - 50, 1136 * 3, 240 * 3 }
	);
	_cColl.SetAddCollider
	(
		ObjectType::MAP,
		ColliderType::BLOCK,
		{ 0, 50, 50, 240 * 3 - 50 }
	);
	_cColl.SetAddCollider
	(
		ObjectType::MAP,
		ColliderType::BLOCK,
		{ 1136 * 3 - 50, 50, 240 * 3 - 50 }
	);
	/*
	_cColl.SetAddCollider
	(
		ObjectType::MAP,
		ColliderType::BLOCK,
		{ 0, 0, 1136 * 3, 50 }
	);
	*/
    return S_OK;
}