#include "Script.h"

#include "Keyboard.h"
#include "ScriptHookV/main.h"
#include "ScriptHookV/natives.h"
#include "ScriptHookV/enums.h"

namespace PistolOnly
{
	bool IsEnabled;

	void DisplayHelpMessage(const char* text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, FALSE, TRUE, -1);
	}

	void ToggleIsEnabled()
	{
		if (IsEnabled)
		{
			IsEnabled = false;
			DisplayHelpMessage("Disabled Pistol Only Mode");
		}
		else
		{
			IsEnabled = true;
			DisplayHelpMessage("Enabled Pistol Only Mode");
		}
	}

	void CheckAndReplaceWeapons()
	{
		const Ped player = PLAYER::PLAYER_PED_ID();
		Hash currentWeapon;
		WEAPON::GET_CURRENT_PED_WEAPON(player, &currentWeapon, TRUE);

		if (currentWeapon != eWeapon::WeaponUnarmed && currentWeapon != eWeapon::WeaponPistol)
		{
			const int pistolAmmoCount = WEAPON::GET_AMMO_IN_PED_WEAPON(player, eWeapon::WeaponPistol);
			WEAPON::REMOVE_ALL_PED_WEAPONS(player, FALSE);
			WEAPON::GIVE_WEAPON_TO_PED(player, eWeapon::WeaponPistol, pistolAmmoCount, FALSE, TRUE);
		}
	}

	[[noreturn]]
	void Run()
	{
		IsEnabled = true;

		while (true)
		{
			if (Input::IsKeyJustUp(VK_F9))
				ToggleIsEnabled();
			if (IsEnabled)
				CheckAndReplaceWeapons();
			WAIT(0);
		}
	}

	[[noreturn]]
	void InitScript()
	{
		Run();
	}
}