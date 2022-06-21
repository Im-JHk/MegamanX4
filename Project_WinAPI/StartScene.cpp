#include "Stdafx.h"
#include "StartScene.h"


HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addFrameImage("title", "Resources/Images/BackGround/title.bmp", 0, 0, 3840 * 3, 480 * 3, 12, 2, true, RGB(255, 0, 255));

	_iAlphaCount = _fBgAlpha = _fTitleAlpha = _fPressAlpha = 0;
	_bIsAlphaIncrese = false;

	_iframeX = 0;
	_iframeY = 1;
	_fAccrueTime = 0;

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	float fDeltaTime = TIMER->GetDeltaTime();
	_fAccrueTime += fDeltaTime;
	if (_fAccrueTime >= 0.1) {
		_iframeX += 1;
		if (_iframeX >= 12) _iframeX = 0;
		_fAccrueTime = 0;
	}

	switch (_iAlphaCount)
	{
	case 1:
		_fBgAlpha = 255;
		_iAlphaCount++;
		break;
	case 2:
		_fTitleAlpha = 255;
		_iAlphaCount++;
		break;
	}

	_fBgAlpha += 2.f;
	if (_fBgAlpha >= 255) {
		_fBgAlpha = 255;
		_fTitleAlpha += 2.f;
	}
	if (_fTitleAlpha >= 255) _fTitleAlpha = 255;

	if (_fPressAlpha == 0 || _fPressAlpha == 255) _bIsAlphaIncrese = !_bIsAlphaIncrese;
	if (_bIsAlphaIncrese) _fPressAlpha += 5.f; else _fPressAlpha -= 5.f;

}

void StartScene::render(void)
{
	IMAGEMANAGER->alphaRender("title", getMemDC(), 0, 0, 0, 0, _fBgAlpha);

	if (_fBgAlpha >= 255 && _fTitleAlpha < 255)
	{
		IMAGEMANAGER->frameRender("title", getMemDC(), 0, 0, 2, 0);
	}
	if (_fTitleAlpha >= 255) {
		IMAGEMANAGER->frameRender("title", getMemDC(), 0, 0, _iframeX, _iframeY);
		if(_fPressAlpha >= 128)	IMAGEMANAGER->frameRender("title", getMemDC(), 0, 0, 1, 0);
	}
}
