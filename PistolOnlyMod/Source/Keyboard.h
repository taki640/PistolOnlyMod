#pragma once
#include <Windows.h>

namespace PistolOnly::Input
{
	void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL altPressed, BOOL wasDown, BOOL isUp);
	bool IsKeyDown(DWORD key);
	bool IsKeyJustUp(DWORD key, bool exclusive = true);
	void ResetKeyState(DWORD key);
}