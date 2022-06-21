#pragma once
#include "Object.h"

class Map : public Object
{
private:
    tagPoint _tPos;
    tagPoint _tMapSize;
public:
    HRESULT Init();

    float GetPosX() { return _tPos.x; }
    float GetPosY() { return _tPos.y; }
    void SetPos(tagPoint pos) { _tPos = pos; }

    Map() {}
    ~Map() {}
};

