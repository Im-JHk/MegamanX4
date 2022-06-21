#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	_startScene = new StartScene;
	_startScene->init();

	_selectScene = new SelectScene;
	_selectScene->init();

	_gameScene = new GameScene;
	_gameScene->init();

	_sceneType = SceneType::START;
	_currentScene = _startScene;
	assert(_currentScene != nullptr);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_startScene);
	SAFE_DELETE(_selectScene);
	SAFE_DELETE(_gameScene);
}

void MainGame::update(void)
{
	GameNode::update();
	
	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))			_selectScene->SetSelect(0);
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))	_selectScene->SetSelect(1);

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		if (_sceneType == SceneType::START) {
			if (_startScene->GetAlphaCount() < 3) {
				_startScene->SetAlphaCount();
			}
			else if (_startScene->GetAlphaCount() == 3) {
				_sceneType = SceneType::SELECT;
				_currentScene = _selectScene;
			}
		}
		else if (_sceneType == SceneType::SELECT) {
			_sceneType = SceneType::GAME;
			_gameScene->SetCharacter(_selectScene->GetSelect());
			_currentScene = _gameScene;
		}
	}
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}

