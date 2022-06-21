#include "Stdafx.h"
#include "Player.h"

HRESULT Player::Init()
{
	//IMAGEMANAGER->addFrameImage("x_intro_end", "Resources/Images/Object/x_intro_end.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("x_move", "Resources/Images/Object/x_move.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("x_move2", "Resources/Images/Object/x_move2.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("x_atk", "Resources/Images/Object/x_atk.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("x_effect", "Resources/Images/Object/x_effect.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("zero_intro_end", "Resources/Images/Object/zero_intro_end.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("zero_move", "Resources/Images/Object/zero_move.bmp", 1920 * 3, 1536 * 3, 15, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("zero_move2", "Resources/Images/Object/zero_move2.bmp", 1920 * 3, 1536 * 3, 15, 12, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("zero_atk", "Resources/Images/Object/zero_atk.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("zero_effect", "Resources/Images/Object/zero_effect.bmp", 1792 * 3, 1536 * 3, 14, 12, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boost_effect", "Resources/Images/Effect/boost_effect.bmp", 0, 0, 560 * 3, 270 * 3, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kick_effect", "Resources/Images/Effect/kick_effect.bmp", 0, 0, 360 * 3, 180 * 3, 8, 4, true, RGB(255, 0, 255));

	_cColl.SetAddCollider
	(
		ObjectType::PLAYER,
		ColliderType::BLOCK,
		{ _tPivotPos.x - 50.f, _tPivotPos.y - 100.f, _tPivotPos.x + 50.f, _tPivotPos.y },
		_tPivotPos,
		{ _tPivotPos },
		{ 50.f, 100.f },
		true
	);

	return S_OK;
}

bool Player::UpdateState()
{
	StateType prev = _eState;

	if (_bIsJumping) _eState = StateType::JUMP;
	else if (_bIsSliding) _eState = StateType::SLIDE;
	else if (_bIsFalling) _eState = StateType::FALL;
	else if (_bIsDash) _eState = StateType::DASH;
	else if (_bIsMove) _eState = StateType::MOVE;
	else _eState = StateType::IDLE;

	if (prev == _eState) return false; else return true;
}

Player::Player() :
	_eType{ ObjectType::PLAYER },
	_eState{ StateType::IDLE },
	_eDirection{ DirectionType::DOWN },
	_tStatus{ 500, 200, 50, 50, 300 },
	_fSpeedPowerX{ 330.f }, _fSpeedPowerY{ 14.f },
	_fSpeedX{ 0 }, _fSpeedY{ 0 },
	_fSpdOrgX{ 0 },
	_bIsIdle{ true },
	_bIsMove{ false },
	_bIsDash{ false },
	_bIsJumping{ false },
	_bIsFalling{ false },
	_bIsSliding{ false },
	_bBoostEffectOn{ false },
	_bKickEffectOn{ false }
{
}

Player::~Player()
{
}
