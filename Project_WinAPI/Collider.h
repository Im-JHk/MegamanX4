#pragma once

class Collider
{
private:
	vector<tagCollider> _vColl;
	vector<tagCollisionInfo> _vCollInfo;
public:
	void Update();

	vector<tagCollider> GetVecCollider() { return _vColl; }
	vector<tagCollisionInfo> GetVecCollisionInfo() { return _vCollInfo; }
	tagCollider			GetCollider(ColliderType type)
	{
		for (auto iter = _vColl.begin(); iter != _vColl.end(); ++iter) {
			if (iter->collType == type) return *iter;
		}
	}
	tagCollider			GetCollider(vector<tagCollider>::iterator iter) { return *iter; }

	void SetCollisionInfo(DirectionType dirType, tagCollider lColl, tagCollider rColl)
	{
		_vCollInfo.push_back({ dirType, lColl, rColl });
	}
	void SetCollInfoClear() { _vCollInfo.clear(); }
	void SetAddCollider(ObjectType objType, ColliderType collType, tagRectangle rect, tagPoint pivPos = {0, 0}, tagPoint relPos = { 0, 0 }, tagPoint scale = { 0, 0 }, bool isAct = true)
	{
		_vColl.push_back({ objType, collType, rect, pivPos, relPos, scale, isAct });
	}
	void SetCollPos(tagPoint pos, ObjectType type)
	{
		for (auto iter = _vColl.begin(); iter != _vColl.end(); ++iter) {
			if (iter->objType == type) {
				iter->rect.left = pos.x - iter->scale.x * 0.5;
				iter->rect.top = pos.y - iter->scale.y;
				iter->rect.right = pos.x + iter->scale.x * 0.5;
				iter->rect.bottom = pos.y;
				iter->pivotPos = pos;
			}
		}
	}
	void SetCollPosPlus(tagPoint pos, ObjectType type)
	{
		for (auto iter = _vColl.begin(); iter != _vColl.end(); ++iter) {
			if (iter->objType == type) {
				iter->rect.left += pos.x;
				iter->rect.top += pos.y;
				iter->rect.right += pos.x;
				iter->rect.bottom += pos.y;
				iter->pivotPos.x += pos.x;
				iter->pivotPos.y += pos.y;
			}
		}
	}

	Collider();
	~Collider();
};

