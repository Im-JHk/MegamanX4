#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init(void)
{
    IMAGEMANAGER->addFrameImage("select", "Resources/Images/BackGround/select.bmp", 0, 0, 960 * 3, 720 * 3, 3, 3, true, RGB(255, 0, 255));

    _iSelect = 0;
    _iframeX = 0;
    _iframeY = 1;
    _fAccrueTime = 0;

    return S_OK;
}

void SelectScene::release(void)
{
}

void SelectScene::update(void)
{
    float fDeltaTime = TIMER->GetDeltaTime();
    _fAccrueTime += fDeltaTime;

    if (_fAccrueTime >= 0.05) {
        _iframeX += 1;
        if (_iframeX >= 3) _iframeX = 0;
        (_iSelect == 0) ? _iframeY = 1 : _iframeY = 2;
        _fAccrueTime = 0;
    }
}

void SelectScene::render(void)
{
    IMAGEMANAGER->frameRender("select", getMemDC(), 0, 0, 0, 0);
    IMAGEMANAGER->frameRender("select", getMemDC(), 0, 0, _iframeX, _iframeY);
}
