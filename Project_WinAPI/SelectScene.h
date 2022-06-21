#pragma once
#include "GameNode.h"

class SelectScene : public GameNode
{
private:
	int _iSelect;
	int _iframeX, _iframeY;
	float _fAccrueTime;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int GetSelect(void) { return _iSelect; }
	void SetSelect(int num) { _iSelect = num; }

	SelectScene() {}
	~SelectScene() {}
};

