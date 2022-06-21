#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	_cPlayer = new Player;
	_cPlayer->Init();
	_cPlayer->SetRelationPos(_cPlayer->GetPivotPos());

	_cStage = new Map;
	_cStage->Init();

	fTimeScale = 1.f;
	_fPrevFrameTime = 0;
	_fEffectFrameTime = 0;
	_fFrameTime = 0;
	_fGravityTime = 0;
	_fDashTime = 0;
	_fJumpKeyDownTime = 0;
	_fStateAccrueTime = 0;

	_tCharacterFrame = {};
	_tEffectStartPos = {};
	_tEffectFrame1 = {};
	_tEffectFrame2 = {};
	_bIsDirChange = false;

	_tCameraPos = {};

	return S_OK;
}

void GameScene::release(void)
{
}

void GameScene::update(void)
{
	float fDeltaTime = TIMER->GetDeltaTime();
	_cPlayer->SetSpdOrgX(_cPlayer->GetPowerX() * fDeltaTime * fTimeScale);
	_fEffectFrameTime += fDeltaTime;
	_fPrevFrameTime += fDeltaTime;
	if (_fPrevFrameTime > 0.02f) {
		_fPrevFrameTime = 0;
		if (_qPrevCharFrame.size() > 5) {
			_qPrevCharFrame.pop_front();
		}
		_qPrevCharFrame.push_back(_cPlayer->GetPivotPos());
	}

	if (KEYMANAGER->isStayKeyDown('X')) {
		if (!_cPlayer->GetIsJumping() && !_cPlayer->GetIsFalling()) {
			_fGravityTime = 0;
			_cPlayer->SetIsJumping(true);
			_cPlayer->SetSpeedY(_cPlayer->GetPowerY());
		}
		if (_cPlayer->GetIsSliding()) {
			_cPlayer->SetIsSliding(false);
			if (_cPlayer->GetDirection() == DirectionType::LEFT) {
				_cPlayer->SetDirection(DirectionType::RIGHT);
				_cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x + _cPlayer->GetSpdOrgX() * 20, _cPlayer->GetPivotPos().y});
				_cPlayer->SetCollPos(_cPlayer->GetPivotPos(), ObjectType::PLAYER);
			}
			else if (_cPlayer->GetDirection() == DirectionType::RIGHT) {
				_cPlayer->SetDirection(DirectionType::LEFT);
				_cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x - _cPlayer->GetSpdOrgX() * 20, _cPlayer->GetPivotPos().y });
				_cPlayer->SetCollPos(_cPlayer->GetPivotPos(), ObjectType::PLAYER);
			}
			_fGravityTime = 0;
			_cPlayer->SetIsJumping(true);
			_cPlayer->SetSpeedY(_cPlayer->GetPowerY() * 0.7);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('X') && _cPlayer->GetIsJumping()) {
		_cPlayer->SetSpeedY(-3.f);
		_fGravityTime = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('Z') && !_cPlayer->GetIsJumping() && !_cPlayer->GetIsFalling() && !_cPlayer->GetIsDash()) {
		_cPlayer->SetIsDash(true);
		_fStateAccrueTime = 0;
		_tPrevDirection = _cPlayer->GetDirection();
	}
	if (KEYMANAGER->isOnceKeyDown('C')) {
		//attack
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_cPlayer->SetDirection(DirectionType::LEFT);
		if (_cPlayer->GetIsDash()) _cPlayer->SetSpeedX(-_cPlayer->GetSpdOrgX() * DASH_CONST);
		else _cPlayer->SetSpeedX(-_cPlayer->GetSpdOrgX());
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_cPlayer->SetDirection(DirectionType::RIGHT);
		if (_cPlayer->GetIsDash()) _cPlayer->SetSpeedX(_cPlayer->GetSpdOrgX() * DASH_CONST);
		else _cPlayer->SetSpeedX(_cPlayer->GetSpdOrgX());
	}
	if (!(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000)) {
		_cPlayer->SetIsMove(false);
		_cPlayer->SetSpeedX(0);
	}
	else if ((GetKeyState(VK_LEFT) & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000)) {
		_cPlayer->SetIsMove(true);
	}

	if (_cPlayer->GetIsJumping() || _cPlayer->GetIsFalling()) {
		if (!_cPlayer->GetIsSliding()) {
			_fGravityTime += fDeltaTime;
			_cPlayer->SetSpeedY(_cPlayer->GetSpeedY() - GRAVITY * _fGravityTime * _fGravityTime);
			_cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x , _cPlayer->GetPivotPos().y - _cPlayer->GetSpeedY() });
			if (_cPlayer->GetSpeedY() < 0) {
				_cPlayer->SetIsJumping(false);
				_cPlayer->SetIsFalling(true);
			}
		}
		else _cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x , _cPlayer->GetPivotPos().y + SLIDE_SPEED });
		_cPlayer->SetCollPos(_cPlayer->GetPivotPos(), ObjectType::PLAYER);
	}
	else if (_cPlayer->GetIsDash() && !_cPlayer->GetIsJumping() && !_cPlayer->GetIsFalling()) {
		_fStateAccrueTime += fDeltaTime;
		if (_fStateAccrueTime < 0.7f) {
			if (_cPlayer->GetDirection() == DirectionType::LEFT) _cPlayer->SetSpeedX(-_cPlayer->GetSpdOrgX() * DASH_CONST);
			else if (_cPlayer->GetDirection() == DirectionType::RIGHT) _cPlayer->SetSpeedX(_cPlayer->GetSpdOrgX() * DASH_CONST);
		}
		else {
			_cPlayer->SetSpeedX(0);
			_cPlayer->SetIsDash(false);
			if (_cPlayer->GetDirection() == DirectionType::LEFT) _tCharacterFrame.x = 6;
			else if (_cPlayer->GetDirection() == DirectionType::RIGHT) _tCharacterFrame.x = 3;
		}
	}

	if (_cPlayer->GetPivotPos().x >= (float)WINSIZE_X * 0.5f) {
		_cPlayer->SetPivotPos({ (float)WINSIZE_X * 0.5, _cPlayer->GetPivotPos().y });
		_tCameraPos.x += _cPlayer->GetSpeedX();
		_cPlayer->SetRelationPos({ _cPlayer->GetRelationPos().x + _cPlayer->GetSpeedX(), _cPlayer->GetRelationPos().y });
	}
	if (_tCameraPos.x <= 0) {
		if (_cPlayer->GetRelationPos().x < (float)WINSIZE_X * 0.5f) {
			_cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x + _cPlayer->GetSpeedX(), _cPlayer->GetPivotPos().y });
		}
		_tCameraPos.x = 0;
		_cPlayer->SetRelationPos({ _cPlayer->GetRelationPos().x + _cPlayer->GetSpeedX(), _cPlayer->GetRelationPos().y });
	}
	if (_tCameraPos.x >= 1136 * 3 - WINSIZE_X) {
		if (_cPlayer->GetRelationPos().x > 1136 * 3 - WINSIZE_X) {
			_cPlayer->SetPivotPos({ _cPlayer->GetPivotPos().x + _cPlayer->GetSpeedX(), _cPlayer->GetPivotPos().y });
		}
		_tCameraPos.x = 1136 * 3 - WINSIZE_X;
		_cPlayer->SetRelationPos({ _cPlayer->GetRelationPos().x + _cPlayer->GetSpeedX(), _cPlayer->GetRelationPos().y });
	}
	_cPlayer->SetCollPos(_cPlayer->GetPivotPos(), ObjectType::PLAYER);

	cout << _tCameraPos.x << endl;
	cout << _cPlayer->GetPivotPos().x << endl;
	cout << _cPlayer->GetRelationPos().x << endl;

	CollisionCheck();
	SetPosFromCollide(_cPlayer);
	_cPlayer->UpdateState() ? UpdateFrame(fDeltaTime, true) : UpdateFrame(fDeltaTime, false);
	ChangeDirection();
	if(!_cPlayer->GetIsDash()) _cPlayer->SetBoostOn(false);
	if (!_cPlayer->GetIsSliding()) _cPlayer->SetKickOn(false);
}

void GameScene::render(void)
{
	//IMAGEMANAGER->moveRender("boss_map", getMemDC(), &RectMake(0, 0, 1136 * 3, WINSIZE_Y), _bgSpeedX);
	//IMAGEMANAGER->loopRender("boss_map", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeedX);

	IMAGEMANAGER->render("boss_map", getMemDC(), 0, 0, _tCameraPos.x, _tCameraPos.y, 1136 * 3, WINSIZE_Y);

	vector<tagCollider> temp(_cPlayer->GetVecCollider());
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
			Rectangle(getMemDC(), iter->rect.left, iter->rect.top, iter->rect.right, iter->rect.bottom);
		}
		temp = _cStage->GetVecCollider();
		for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
			Rectangle(getMemDC(), iter->rect.left, iter->rect.top, iter->rect.right, iter->rect.bottom);
		}
	}
	if (_iSelectCharacter == 0) {
		if (_cPlayer->GetIsDash()) {
			for (auto i = _qPrevCharFrame.begin(); i != _qPrevCharFrame.end(); ++i) {
				IMAGEMANAGER->frameRender("x_move2", getMemDC(), i->x - 192, i->y - 256, _tCharacterFrame.x, _tCharacterFrame.y);
			}
		}
		IMAGEMANAGER->frameRender("x_move", getMemDC(), _cPlayer->GetPivotPos().x - 192, _cPlayer->GetPivotPos().y - 256, _tCharacterFrame.x, _tCharacterFrame.y);
	}
	else {
		if (_cPlayer->GetIsDash()) {
			for (auto i = _qPrevCharFrame.begin(); i != _qPrevCharFrame.end(); ++i) {
				IMAGEMANAGER->frameRender("zero_move2", getMemDC(), i->x - 192, i->y - 256, _tCharacterFrame.x, _tCharacterFrame.y);
			}
		}
		IMAGEMANAGER->frameRender("zero_move", getMemDC(), _cPlayer->GetPivotPos().x - 192, _cPlayer->GetPivotPos().y - 256, _tCharacterFrame.x, _tCharacterFrame.y);
	}
	if (_cPlayer->GetBoostOn() && !_cPlayer->GetIsJumping() && !_cPlayer->GetIsFalling()) {
		if (_cPlayer->GetDirection() == DirectionType::LEFT) {
			IMAGEMANAGER->frameRender("boost_effect", getMemDC(), _cPlayer->GetPivotPos().x, _cPlayer->GetPivotPos().y - 135, _tEffectFrame1.x, _tEffectFrame1.y);
			IMAGEMANAGER->frameRender("boost_effect", getMemDC(), _tEffectStartPos.x, _tEffectStartPos.y - 100, _tEffectFrame2.x, _tEffectFrame2.y);
		}
		else if (_cPlayer->GetDirection() == DirectionType::RIGHT) {
			IMAGEMANAGER->frameRender("boost_effect", getMemDC(), _cPlayer->GetPivotPos().x - 210, _cPlayer->GetPivotPos().y - 135, _tEffectFrame1.x, _tEffectFrame1.y);
			IMAGEMANAGER->frameRender("boost_effect", getMemDC(), _tEffectStartPos.x - 210, _tEffectStartPos.y - 100, _tEffectFrame2.x, _tEffectFrame2.y);
		}
	}
	else if (_cPlayer->GetKickOn() && _tEffectFrame1.x < 7) {
		if (_cPlayer->GetDirection() == DirectionType::LEFT) {
			IMAGEMANAGER->frameRender("kick_effect", getMemDC(), _cPlayer->GetPivotPos().x - 110, _cPlayer->GetPivotPos().y - 120, _tEffectFrame1.x, _tEffectFrame1.y);
		}
		else if (_cPlayer->GetDirection() == DirectionType::RIGHT) {
			IMAGEMANAGER->frameRender("kick_effect", getMemDC(), _cPlayer->GetPivotPos().x - 20, _cPlayer->GetPivotPos().y - 120, _tEffectFrame1.x, _tEffectFrame1.y);
		}
	}

	
}

void GameScene::CollisionCheck()
{
	int collCount = 0;
	tagCollider playerColl = _cPlayer->GetCollider(ColliderType::BLOCK);
	vector<tagCollider> stageColl = _cStage->GetVecCollider();

	for (vector<tagCollider>::iterator iter = stageColl.begin(); iter != stageColl.end(); ++iter) {
		if (DirectionType::LEFT == COLLISIONMANAGER->CheckCollision(playerColl, *iter)) {
			_cPlayer->SetCollisionInfo(DirectionType::LEFT, playerColl, *iter);
			collCount++;
		}
		else if (DirectionType::RIGHT == COLLISIONMANAGER->CheckCollision(playerColl, *iter)) {
			_cPlayer->SetCollisionInfo(DirectionType::RIGHT, playerColl, *iter);
			collCount++;
		}
		else if (DirectionType::UP == COLLISIONMANAGER->CheckCollision(playerColl, *iter)) {
			_cPlayer->SetCollisionInfo(DirectionType::UP, playerColl, *iter);
			collCount++;
		}
		else if (DirectionType::DOWN == COLLISIONMANAGER->CheckCollision(playerColl, *iter)) {
			_cPlayer->SetCollisionInfo(DirectionType::DOWN, playerColl, *iter);
			collCount++;
		}
		if (collCount >= 2) break;
	}
}

void GameScene::SetPosFromCollide(Player* obj)
{
	vector<tagCollisionInfo> tempVec = obj->GetVecCollisionInfo();
	bool isFalling = true;
	bool isSliding = false;

	for (vector<tagCollisionInfo>::iterator iter = tempVec.begin(); iter != tempVec.end(); ++iter) {
		if (DirectionType::LEFT == iter->dirType) {
			obj->SetPivotPos({ iter->rColl.rect.right + iter->lColl.scale.x * 0.5f, obj->GetPivotPos().y });
			obj->SetCollPos(obj->GetPivotPos(), ObjectType::PLAYER);
			if (obj->GetIsFalling()) {
				obj->SetIsSliding(true);
				obj->SetIsDash(false);
				_fGravityTime = 0;
				isSliding = true;
			}
			else {
				obj->SetIsSliding(false);
				isSliding = false;
			}
		}
		else if (DirectionType::RIGHT == iter->dirType) {
			obj->SetPivotPos({ iter->rColl.rect.left - iter->lColl.scale.x * 0.5f, obj->GetPivotPos().y });
			obj->SetCollPos(obj->GetPivotPos(), ObjectType::PLAYER);
			if (obj->GetIsFalling()) {
				obj->SetIsSliding(true);
				obj->SetIsDash(false);
				_fGravityTime = 0;
				isSliding = true;
			}
			else {
				obj->SetIsSliding(false);
				isSliding = false;
			}
		}
		else if (DirectionType::UP == iter->dirType) {
			obj->SetPivotPos({ obj->GetPivotPos().x, iter->rColl.rect.bottom + iter->lColl.scale.y });
			obj->SetCollPos(obj->GetPivotPos(), ObjectType::PLAYER);
		}
		else if (DirectionType::DOWN == iter->dirType) {
			obj->SetPivotPos({ obj->GetPivotPos().x, iter->rColl.rect.top });
			obj->SetCollPos(obj->GetPivotPos(), ObjectType::PLAYER);
			obj->SetSpeedY(0);
			if (obj->GetIsJumping() || obj->GetIsFalling()) {
				obj->SetIsDash(false);
			}
			obj->SetIsJumping(false);
			obj->SetIsFalling(false);
			obj->SetIsSliding(false);
			_fGravityTime = 0;
			isFalling = false;
			isSliding = false;
		}
	}
	if (isFalling) {
		obj->SetIsFalling(true);
	}
	else if (!isFalling) {
		obj->SetIsFalling(false);
	}
	if (isSliding) {
		obj->SetIsSliding(true);
	}
	else if (!isSliding) {
		obj->SetIsSliding(false);
	}
	obj->SetCollInfoClear();
}

void GameScene::UpdateFrame(float deltaTime, bool update)
{
	_fFrameTime += deltaTime;
	StateType state = _cPlayer->GetState();
	if (update) {
		if (_cPlayer->GetDirection() == DirectionType::RIGHT) {
			if (state == StateType::IDLE) _tCharacterFrame = { 0, 0 };
			else if (state == StateType::MOVE) _tCharacterFrame = { 0, 2 };
			else if (state == StateType::DASH) {
				_cPlayer->SetBoostOn(true);
				_tCharacterFrame = { 0, 4 };
				if (_iSelectCharacter == 0) _tEffectFrame1 = { 0, 0 };
				else _tEffectFrame1 = { 0, 2 };
				_tEffectStartPos = _cPlayer->GetPivotPos();
				_tEffectFrame2 = { 0, 4 };
			}
			else if (state == StateType::JUMP) _tCharacterFrame = { 0, 6 };
			else if (state == StateType::FALL) _tCharacterFrame = { 6, 6 };
			else if (state == StateType::SLIDE) {
				_cPlayer->SetKickOn(true);
				_tCharacterFrame = { 1, 8 };
				_tEffectFrame1 = { 0, 0 };
			}
			else if (state == StateType::DAMAGE) _tCharacterFrame = { 0, 10 };
		}
		else if (_cPlayer->GetDirection() == DirectionType::LEFT) {
			if (state == StateType::IDLE) _tCharacterFrame = { 3, 1 };
			else if (state == StateType::MOVE) _tCharacterFrame = { 13, 3 };
			else if (state == StateType::DASH) {
				_cPlayer->SetBoostOn(true);
				_tCharacterFrame = { 9, 5 };
				if (_iSelectCharacter == 0) _tEffectFrame1 = { 0, 1 };
				else _tEffectFrame1 = { 0, 3 };
				_tEffectStartPos = _cPlayer->GetPivotPos();
				_tEffectFrame2 = { 0, 5 };
			}
			else if (state == StateType::JUMP) _tCharacterFrame = { 10, 7 };
			else if (state == StateType::FALL) _tCharacterFrame = { 4, 7 };
			else if (state == StateType::SLIDE) {
				_cPlayer->SetKickOn(true);
				_tCharacterFrame = { 3, 9 };
				_tEffectFrame1 = { 0, 1 };
			}
			else if (state == StateType::DAMAGE) _tCharacterFrame = { 4, 11 };
		}
	}
	switch (_tCharacterFrame.y)
	{
	case 0:
		if (_fFrameTime > 0.2) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x > 3) _tCharacterFrame.x = 0;
		break;
	case 1:
		if (_fFrameTime > 0.2) {
			_fFrameTime = 0;
			_tCharacterFrame.x -= 1;
		}
		if (_tCharacterFrame.x < 0) _tCharacterFrame.x = 3;
		break;
	case 2:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x > 13) _tCharacterFrame.x = 0;
		break;
	case 3:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x -= 1;
		}
		if (_tCharacterFrame.x < 0) _tCharacterFrame.x = 13;
		break;
	case 4:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x > 9) _tCharacterFrame.x = 0;
		break;
	case 5:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x -= 1;
		}
		if (_tCharacterFrame.x < 0) _tCharacterFrame.x = 9;
		break;
	case 6:
		if (_fFrameTime > 0.2) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x > 10) _tCharacterFrame.x = 0;
		break;
	case 7:
		if (_fFrameTime > 0.2) {
			_fFrameTime = 0;
			_tCharacterFrame.x -= 1;
		}
		if (_tCharacterFrame.x < 0) _tCharacterFrame.x = 10;
		break;
	case 8:
		if (_fFrameTime > 0.3) {
			_fFrameTime = 0;
			if (_tCharacterFrame.x < 3) _tCharacterFrame.x += 1;
		}
		break;
	case 9:
		if (_fFrameTime > 0.3) {
			_fFrameTime = 0;
			if (_tCharacterFrame.x > 2) _tCharacterFrame.x -= 1;
		}
		break;
	case 10:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x > 4) _tCharacterFrame.x = 0;
		break;
	case 11:
		if (_fFrameTime > 0.1) {
			_fFrameTime = 0;
			_tCharacterFrame.x += 1;
		}
		if (_tCharacterFrame.x < 0) _tCharacterFrame.x = 4;
		break;
	}
	
	if (_tEffectFrame1.y >= 0 && _tEffectFrame1.y <= 3) {
		if (_fEffectFrameTime > 0.1) {
			_fEffectFrameTime = 0;
			if (_cPlayer->GetBoostOn()) {
				if (_tEffectFrame2.x < 7) _tEffectFrame2.x += 1;
				if (_tEffectFrame1.x < 7) _tEffectFrame1.x += 1;
			}
			if (_cPlayer->GetKickOn()) {
				_tEffectFrame1.x += 1;
				if (_tEffectFrame1.x > 7) _tEffectFrame1.x = 0;
			}
		}
	}
}

void GameScene::ChangeDirection()
{
	if (_cPlayer->GetDirection() == DirectionType::RIGHT) {
		switch (_tCharacterFrame.y)
		{
		case 0:
		case 1:
			_tCharacterFrame.y = 0;
			break;
		case 2:
		case 3:
			_tCharacterFrame.y = 2;
			break;
		case 4:
		case 5:
			_tCharacterFrame.y = 4;
			break;
		case 6:
		case 7:
			_tCharacterFrame.y = 6;
			break;
		case 8:
		case 9:
			_tCharacterFrame.y = 8;
			break;
		case 10:
		case 11:
			_tCharacterFrame.y = 10;
			break;
		}
	}
	else if (_cPlayer->GetDirection() == DirectionType::LEFT) {
		switch (_tCharacterFrame.y)
		{
		case 0:
		case 1:
			_tCharacterFrame.y = 1;
			break;
		case 2:
		case 3:
			_tCharacterFrame.y = 3;
			break;
		case 4:
		case 5:
			_tCharacterFrame.y = 5;
			break;
		case 6:
		case 7:
			_tCharacterFrame.y = 7;
			break;
		case 8:
		case 9:
			_tCharacterFrame.y = 9;
			break;
		case 10:
		case 11:
			_tCharacterFrame.y = 11;
			break;
		}
	}
}
