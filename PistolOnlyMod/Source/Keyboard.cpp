#include "Keyboard.h"

// taken from NativeTrainer sample from ScriptHookV SDK
namespace PistolOnly::Input
{
	constexpr int KEYS_SIZE = 255;
	constexpr int NOW_PERIOD_MS = 100;
	constexpr int MAX_DOWN_MS = 5000;

	struct
	{
		DWORD Time;
		BOOL AltPressed;
		BOOL WasDown;
		BOOL IsUp;
	} KeyStates[KEYS_SIZE];

	void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL altPressed, BOOL wasDown, BOOL isUp)
	{
		if (key < KEYS_SIZE)
		{
			KeyStates[key].Time = GetTickCount();
			KeyStates[key].AltPressed = altPressed;
			KeyStates[key].WasDown = wasDown;
			KeyStates[key].IsUp = isUp;
		}
	}

	bool IsKeyDown(DWORD key)
	{
		return key < KEYS_SIZE ? GetTickCount() < KeyStates[key].Time + MAX_DOWN_MS && !KeyStates[key].IsUp : false;
	}

	bool IsKeyJustUp(DWORD key, bool exclusive)
	{
		const bool value = key < KEYS_SIZE ? GetTickCount() < KeyStates[key].Time + NOW_PERIOD_MS && KeyStates[key].IsUp : false;
		if (value && exclusive)
			ResetKeyState(key);
		return value;
	}

	void ResetKeyState(DWORD key)
	{
		if (key < KEYS_SIZE)
			memset(&KeyStates[key], 0, sizeof(KeyStates[0]));
	}
}