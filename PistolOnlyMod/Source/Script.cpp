#include "Script.h"

#include "ScriptHookV/main.h"
#include "ScriptHookV/natives.h"
#include "ScriptHookV/enums.h"
#include "Keyboard.h"

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

	bool IsPlayingPrologue(const Ped& player)
	{
		const Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0.0f, 0.0f, 0.0f);
		// i hate this, would be better to check the mission name instead of location.
		// i found a stat called MISSION_NAME but couldn't get the value of it.
		return strcmp(ZONE::GET_NAME_OF_ZONE(pos.x, pos.y, pos.z), "PROL") == 0;
	}

	bool IsPlayerTrevor(const Ped& player)
	{
		return PED::IS_PED_MODEL(player, MISC::GET_HASH_KEY("PLAYER_TWO"));	// PLAYER_TWO = trevor model
	}

	void CheckAndReplaceWeapons()
	{
		const Ped player = PLAYER::PLAYER_PED_ID();
		Hash currentWeapon;
		WEAPON::GET_CURRENT_PED_WEAPON(player, &currentWeapon, TRUE);

		if (currentWeapon != eWeapon::WeaponUnarmed && currentWeapon != eWeapon::WeaponPistol)
		{
			int pistolAmmoCount = WEAPON::GET_AMMO_IN_PED_WEAPON(player, eWeapon::WeaponPistol);

			static bool fixedPrologueSoftlock = false;
			if (!fixedPrologueSoftlock && IsPlayingPrologue(player) && IsPlayerTrevor(player))
			{
				// during prologue the player has no pistol ammo and the
				// player cannot proceed the scene where trevor saves michael
				if (pistolAmmoCount == 0)
				{
					pistolAmmoCount = 1;
					// this is ok to be set to true here because the first time
					// the player controls trevor is where the softlock happens
					fixedPrologueSoftlock = true;
				}
			}

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