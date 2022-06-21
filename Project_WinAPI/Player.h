#pragma once
#include "Object.h"

class Player :
    public Object
{
private:
    vector<StateType> _vState;
    CharacterType _eCharacter;
    ObjectType _eType;
    StateType _eState;
    DirectionType _eDirection;
    tagUnit _tStatus;

    float _fSpeedPowerX, _fSpeedPowerY;
    float _fSpeedX, _fSpeedY;
    float _fSpdOrgX;

    bool _bIsIdle;
    bool _bIsMove;
    bool _bIsDash;
    bool _bIsJumping;
    bool _bIsFalling;
    bool _bIsSliding;

    bool _bBoostEffectOn;
    bool _bKickEffectOn;
public:
    HRESULT Init();

    vector<StateType> GetVecState() { return _vState; }
    void              SetVecState(StateType st) { _vState.push_back(st); }
    void              ClearVecState() { _vState.clear(); }

    float GetPowerX() { return _fSpeedPowerX; }
    float GetPowerY() { return _fSpeedPowerY; }
    float GetSpeedX() { return _fSpeedX; }
    float GetSpeedY() { return _fSpeedY; }
    float GetSpdOrgX() { return _fSpdOrgX; }

    void SetSpeedX(float spd) { _fSpeedX = spd; }
    void SetSpeedY(float spd) { _fSpeedY = spd; }
    void SetSpdOrgX(float spd) { _fSpdOrgX = spd; }

    DirectionType GetDirection() { return _eDirection; }
    StateType GetState() { return _eState; }
    bool GetIsMove() { return _bIsMove; }
    bool GetIsDash() { return _bIsDash; }
    bool GetIsJumping() { return _bIsJumping; }
    bool GetIsFalling() { return _bIsFalling; }
    bool GetIsSliding() { return _bIsSliding; }
    bool GetBoostOn() { return _bBoostEffectOn; }
    bool GetKickOn() { return _bKickEffectOn; }

    void SetDirection(DirectionType dir) { _eDirection = dir; }
    void SetState(StateType state) { _eState = state; }
    void SetIsMove(bool b) { _bIsMove = b; }
    void SetIsDash(bool b) { _bIsDash = b; }
    void SetIsJumping(bool b) { _bIsJumping = b; }
    void SetIsFalling(bool b) { _bIsFalling = b; }
    void SetIsSliding(bool b) { _bIsSliding = b; }
    void SetBoostOn(bool b) { _bBoostEffectOn = b; }
    void SetKickOn(bool b) { _bKickEffectOn = b; }

    tagUnit GetStatus() { return _tStatus; }
    int GetHP() { return _tStatus.hp; }
    int GetMP() { return _tStatus.mp; }
    int GetATK() { return _tStatus.atk; }
    int GetDEF() { return _tStatus.def; }
    int GetSPD() { return _tStatus.spd; }

    void SetHP(int hp) { _tStatus.hp = hp; }
    void SetMP(int mp) { _tStatus.mp = mp; }
    void SetATK(int atk) { _tStatus.atk = atk; }
    void SetDEF(int def) { _tStatus.def = def; }
    void SetSPD(int spd) { _tStatus.spd = spd; }
    void SetCharacter(int num) { _eCharacter = static_cast<CharacterType>(num); }

    bool UpdateState();

    Player();
    ~Player();
};

