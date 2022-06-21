#include "Stdafx.h"
#include "SingletonBase.h"
#include "Timer.h"

HRESULT Timer::Init(void)
{
	QueryPerformanceCounter(&_tPrevCount);
	QueryPerformanceFrequency(&_tFrequency);

	return S_OK;
}

void Timer::Update(void)
{
	QueryPerformanceCounter(&_tCurrCount);
	_fDeltaTime = (_tCurrCount.QuadPart - _tPrevCount.QuadPart) / (float)_tFrequency.QuadPart;
	_tPrevCount = _tCurrCount;
}