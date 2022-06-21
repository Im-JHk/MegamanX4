#pragma once
#include "State.h"

struct tagPoint
{
	float x;
	float y;
};

struct tagRectangle
{
	float left;
	float top;
	float right;
	float bottom;
};

struct tagCollider
{
	ObjectType objType;
	ColliderType collType;
	tagRectangle rect;
	tagPoint pivotPos;
	tagPoint relativePos;
	tagPoint scale;
	bool isActivate;
};

struct tagCollisionInfo
{
	DirectionType dirType;
	tagCollider lColl;
	tagCollider rColl;
};

struct tagUnit
{
	int hp;
	int mp;
	int atk;
	int def;
	int spd;
};
/*
tagPoint operator +(const tagPoint& p1, const tagPoint& p2)
{
	tagPoint temp = { p1.x + p2.x, p1.y + p2.y };
	return temp;
}

tagRectangle operator +(const tagRectangle& r, const tagPoint& p)
{
	tagRectangle temp = { r.left + p.x, r.top + p.y, r.right + p.x, r.bottom + p.y };
	return temp;
}
*/