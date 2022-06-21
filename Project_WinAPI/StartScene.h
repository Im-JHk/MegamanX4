#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	int _iAlphaCount;
	float _fBgAlpha;
	float _fTitleAlpha;
	float _fPressAlpha;
	bool _bIsAlphaIncrese;

	int _iframeX, _iframeY;
	float _fAccrueTime;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int GetAlphaCount() { return _iAlphaCount; }
	void SetAlphaCount() { _iAlphaCount++; }

	StartScene() {}
	~StartScene() {}
};

