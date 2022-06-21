#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Map.h"

class GameScene : public GameNode
{
private:
	Player* _cPlayer;
	Map* _cStage;

	DirectionType _tPrevDirection;
	deque<tagPoint> _qPrevCharFrame;
 
	tagPoint _tEffectStartPos;
	POINT _tEffectFrame1;
	POINT _tEffectFrame2;
	POINT _tCharacterFrame;

	POINT _tCameraPos;

	int _iSelectCharacter;

	float _fPrevFrameTime;
	float _fEffectFrameTime;
	float _fFrameTime;
	float _fGravityTime;
	float _fDashTime;
	float _fJumpKeyDownTime;
	float _fStateAccrueTime;

	bool _bIsDirChange;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CollisionCheck();
	void SetPosFromCollide(Player* obj);
	void SetCharacter(int num) { _iSelectCharacter = num; }

	void UpdateFrame(float deltaTime, bool update);
	void ChangeDirection();

	GameScene() {}
	~GameScene() {}
};

