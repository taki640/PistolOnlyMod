#include "Script.h"
#include "ScriptHookV/main.h"

namespace PistolOnly
{
	[[noreturn]]
	void Run()
	{
		while (true)
		{
			WAIT(0);
		}
	}

	[[noreturn]]
	void InitScript()
	{
		Run();
	}
}