#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "GameScene.h"

class MainGame :public GameNode
{
private:
	SceneType _sceneType;

	StartScene* _startScene;
	SelectScene* _selectScene;
	GameScene* _gameScene;
	GameNode* _currentScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}
};

