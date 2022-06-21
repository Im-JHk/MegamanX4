#pragma once
#include "Collider.h"

class Object 
{
protected:
	tagPoint _tPivotPos;
	tagPoint _tRelationPos;
	Collider _cColl;
public:
	virtual HRESULT Init(void);
	virtual void Update(void);
	virtual void Release(void);

public:
	void SetPivotPos(tagPoint pos) { _tPivotPos = pos; }
	void SetRelationPos(tagPoint pos) { _tRelationPos = pos; }
	void SetCollPos(tagPoint pos, ObjectType type) { _cColl.SetCollPos(pos, type); }
	void SetCollPosPlus(tagPoint pos, ObjectType type) { _cColl.SetCollPosPlus(pos, type); }
	void SetCollisionInfo(DirectionType dirType, tagCollider lColl, tagCollider rColl)
	{
		_cColl.SetCollisionInfo(dirType, lColl, rColl);
	}
	void SetCollInfoClear() { _cColl.SetCollInfoClear(); }

	tagPoint GetPivotPos() { return _tPivotPos; }
	tagPoint GetRelationPos() { return _tRelationPos; }
	vector<tagCollider> GetVecCollider() { return _cColl.GetVecCollider(); }
	vector<tagCollisionInfo> GetVecCollisionInfo() { return _cColl.GetVecCollisionInfo(); }
	tagCollider GetCollider(ColliderType type) { return _cColl.GetCollider(type); }

	Object();
	~Object();
};

