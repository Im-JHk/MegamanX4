#include "Stdafx.h"
#include "GameNode.h"
#include "Object.h"

HRESULT Object::Init(void)
{
	return S_OK;
}

void Object::Update(void)
{

}

void Object::Release(void)
{
}

Object::Object() : _tPivotPos{150.f, WINSIZE_Y - 100.f}, _tRelationPos{ 150.f, WINSIZE_Y - 100.f }
{
}

Object::~Object()
{
}
