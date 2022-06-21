#pragma once

static float fTimeScale;

class Timer : public SingletonBase <Timer>
{
private:
	LARGE_INTEGER _tPrevCount, _tCurrCount, _tFrequency;
	float _fDeltaTime;
public:
	HRESULT Init(void);
	void Update(void);

public:
	float GetDeltaTime() { return _fDeltaTime; }

	Timer() {}
	~Timer() {}
};

