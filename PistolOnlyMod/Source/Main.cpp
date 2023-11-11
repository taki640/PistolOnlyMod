#include "Keyboard.h"
#include "Script.h"
#include "ScriptHookV/main.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, PistolOnly::InitScript);
		keyboardHandlerRegister(PistolOnly::Input::OnKeyboardMessage);
		break;
	case DLL_PROCESS_DETACH:
		scriptUnregister(hInstance);
		keyboardHandlerUnregister(PistolOnly::Input::OnKeyboardMessage);
		break;
	default: break;
	}

	return TRUE;
}