#pragma once
#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

//! Windows ��� ����
#include <Windows.h>
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <assert.h>

//! C++ ��Ÿ�� ��� ����
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <deque>
#include <map>
#include <cassert>
using namespace std;

//===================================
// # ���� ���� ��������� �̰��� �߰� #
//===================================
#include "Struct.h"
#include "State.h"

#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "Timer.h"

#define GRAVITY 5.f
#define DASH_CONST 2.5
#define BASE_SPEED 300
#define SLIDE_SPEED 3.f


//========================
// # �̱����� �̰��� �߰� #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define COLLISIONMANAGER CollisionManager::getSingleton()
#define TIMER Timer::getSingleton()

//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920
#define WINSTART_Y	 0
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X	 400
#define WINSTART_Y	 100
#define WINSIZE_X	 320 * 3
#define WINSIZE_Y	 240 * 3
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif

//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;