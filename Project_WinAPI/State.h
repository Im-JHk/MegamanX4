#pragma once

enum class SceneType
{
	START,
	SELECT,
	GAME
};

enum class CharacterType
{
	X,
	ZERO
};

enum class StateType
{
	IDLE,
	MOVE,
	DASH,
	JUMP,
	FALL,
	SLIDE,
	ATTACK,
	DAMAGE
};

enum class ObjectType
{
	NONE,
	PLAYER,
	ENEMY,
	MAP
};

enum class ColliderType
{
	BLOCK,
	RANGE,
	ATTACK
};

enum class DirectionType
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};