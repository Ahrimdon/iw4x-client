#include "STDInclude.hpp"

namespace Components
{
	Game::XAssetHeader Weapon::WeaponFileLoad(Game::XAssetType /*type*/, std::string filename)
	{
		Game::XAssetHeader header = { nullptr };

		// Try loading raw weapon
		if (FileSystem::File(Utils::String::VA("weapons/mp/%s", filename.data())).exists())
		{
			header.data = Game::BG_LoadWeaponDef_LoadObj(filename.data());
		}

		return header;
	}

	const char* Weapon::GetWeaponConfigString(int index)
	{
		int weaponIndex = index - 2804;

		if(weaponIndex < 1200)
		{
			return Game::CL_GetConfigString(index);
		}
		else
		{
			return Game::CL_GetConfigString(weaponIndex + 2939);
		}
	}

	void Weapon::SaveRegisteredWeapons()
	{
		*reinterpret_cast<DWORD*>(0x1A86098) = 0;

		if (Game::BG_GetNumWeapons() > 1u)
		{
			for (unsigned int i = 1; i < Game::BG_GetNumWeapons() && i < 1200; ++i)
			{
				Game::SV_SetConfigstring(i + 2804, Game::BG_GetWeaponName(i));
			}
		}

		if (Game::BG_GetNumWeapons() > 1200)
		{
			for (unsigned int i = 1200; i < Game::BG_GetNumWeapons(); ++i)
			{
				Game::SV_SetConfigstring(i + 2939, Game::BG_GetWeaponName(i));
			}
		}
	}

	void Weapon::PatchConfigStrings()
	{
		Utils::Hook::Set<DWORD>(0x4347A7, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x4982F4, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x4F88B6, MAX_CONFIGSTRINGS); // Save file
		Utils::Hook::Set<DWORD>(0x5A1FA7, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x5A210D, MAX_CONFIGSTRINGS); // Game state
		Utils::Hook::Set<DWORD>(0x5A840E, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x5A853C, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x5AC392, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x5AC3F5, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x5AC542, MAX_CONFIGSTRINGS); // Game state
		Utils::Hook::Set<DWORD>(0x5EADF0, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x625388, MAX_CONFIGSTRINGS);
		Utils::Hook::Set<DWORD>(0x625516, MAX_CONFIGSTRINGS);

		static short configStrings[MAX_CONFIGSTRINGS];
		Utils::Hook::Set(0x405B72, configStrings);
		Utils::Hook::Set(0x468508, configStrings);
		Utils::Hook::Set(0x47FD7C, configStrings);
		Utils::Hook::Set(0x49830E, configStrings);
		Utils::Hook::Set(0x498371, configStrings);
		Utils::Hook::Set(0x4983D5, configStrings);
		Utils::Hook::Set(0x4A74AD, configStrings);
		Utils::Hook::Set(0x4BAE7C, configStrings);
		Utils::Hook::Set(0x4BAEC3, configStrings);
		Utils::Hook::Set(0x6252F5, configStrings);
		Utils::Hook::Set(0x625372, configStrings);
		Utils::Hook::Set(0x6253D3, configStrings);
		Utils::Hook::Set(0x625480, configStrings);
		Utils::Hook::Set(0x6254CB, configStrings);

		// TODO: Check if all of these actually mark the end of the array
		Utils::Hook::Set(0x405B8F, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x459121, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x45A476, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x49FD56, &configStrings[sizeof(configStrings)]);
		Utils::Hook::Set(0x4A74C9, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x4C8196, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x4EBCE6, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x4F36D6, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x6081C4, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x608211, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x608274, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x6083D6, &configStrings[sizeof(configStrings)]);
		//Utils::Hook::Set(0x60848E, &configStrings[sizeof(configStrings)]);


		// Patch client config strings
		// The structure below is completely guessed and might be totally wrong
		struct
		{
			int indexList[MAX_CONFIGSTRINGS];
			char stringList[131072];
			int count;
		} clConfigStrings;

		Utils::Hook::Set<DWORD>(0x44A333, sizeof(clConfigStrings));
		Utils::Hook::Set<DWORD>(0x5A1F56, sizeof(clConfigStrings));
		Utils::Hook::Set<DWORD>(0x5A2043, sizeof(clConfigStrings));

		Utils::Hook::Set<DWORD>(0x5A2053, sizeof(clConfigStrings.indexList));
		Utils::Hook::Set<DWORD>(0x5A2098, sizeof(clConfigStrings.indexList));
		Utils::Hook::Set<DWORD>(0x5AC32C, sizeof(clConfigStrings.indexList));

		Utils::Hook::Set(0x4235AC, &clConfigStrings.indexList);
		Utils::Hook::Set(0x434783, &clConfigStrings.indexList);
		Utils::Hook::Set(0x44A339, &clConfigStrings.indexList);
		Utils::Hook::Set(0x44ADB7, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A1FE6, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A2048, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A205A, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A2077, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A2091, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A20D7, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A83FF, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A84B0, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5A84E5, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5AC333, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5AC44A, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5AC4F3, &clConfigStrings.indexList);
		Utils::Hook::Set(0x5AC57A, &clConfigStrings.indexList);

		Utils::Hook::Set(0x4235B7, &clConfigStrings.stringList);
		Utils::Hook::Set(0x43478D, &clConfigStrings.stringList);
		Utils::Hook::Set(0x44ADBC, &clConfigStrings.stringList);
		Utils::Hook::Set(0x5A1FEF, &clConfigStrings.stringList);
		Utils::Hook::Set(0x5A20E6, &clConfigStrings.stringList);
		Utils::Hook::Set(0x5AC457, &clConfigStrings.stringList);
		Utils::Hook::Set(0x5AC502, &clConfigStrings.stringList);
		Utils::Hook::Set(0x5AC586, &clConfigStrings.stringList);

		Utils::Hook::Set(0x5A2071, &clConfigStrings.count);
		Utils::Hook::Set(0x5A20CD, &clConfigStrings.count);
		Utils::Hook::Set(0x5A20DC, &clConfigStrings.count);
		Utils::Hook::Set(0x5A20F3, &clConfigStrings.count);
		Utils::Hook::Set(0x5A2104, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC33F, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC43B, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC450, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC463, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC471, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC4C3, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC4E8, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC4F8, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC50F, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC528, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC56F, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC580, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC592, &clConfigStrings.count);
		Utils::Hook::Set(0x5AC59F, &clConfigStrings.count);
	}

	void Weapon::PatchLimit()
	{
		Utils::Hook::Set<DWORD>(0x403783, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x403E8C, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x41BC34, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x42EB42, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x44FA7B, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x474E0D, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x48E8F2, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x492647, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x494585, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x4945DB, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x4B1F96, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x4D4A99, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x4DD566, WEAPON_LIMIT);
		//Utils::Hook::Set<DWORD>(0x4E3683, WEAPON_LIMIT); // Configstring
		Utils::Hook::Set<DWORD>(0x58609F, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x586CAE, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x58F7BE, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x58F7D9, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x58F82D, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5D6C8B, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5D6CF7, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5E24D5, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5E2604, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5E2828, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5E2B4F, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5E366C, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5F2614, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5F7187, WEAPON_LIMIT);
		Utils::Hook::Set<DWORD>(0x5FECF9, WEAPON_LIMIT);

		//Utils::Hook(0x4BD52D, Weapon::GetWeaponConfigString, HOOK_CALL).install()->quick();
		//Utils::Hook(0x45D170, Weapon::SaveRegisteredWeapons, HOOK_JUMP).install()->quick();

		static int bg_weaponCompleteDefs[WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4B35E1, sizeof(bg_weaponCompleteDefs));
		Utils::Hook::Set(0x44CE07, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x45C671, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x45C6A4, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x4B35E8, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x4B3643, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x4CE903, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x4CE927, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x4E6EC7, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57B69A, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57B910, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57B925, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57BA22, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57BA51, bg_weaponCompleteDefs);
		Utils::Hook::Set(0x57BA78, bg_weaponCompleteDefs);

		static int bg_weaponDefs[WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4B35F2, sizeof(bg_weaponDefs));
		Utils::Hook::Set(0x42F697, bg_weaponDefs);
		Utils::Hook::Set(0x440EB7, bg_weaponDefs);
		Utils::Hook::Set(0x45C67D, bg_weaponDefs);
		Utils::Hook::Set(0x45C685, bg_weaponDefs);
		Utils::Hook::Set(0x45C6B0, bg_weaponDefs);
		Utils::Hook::Set(0x4B35F9, bg_weaponDefs);
		Utils::Hook::Set(0x4B364B, bg_weaponDefs);
		Utils::Hook::Set(0x57B693, bg_weaponDefs);
		Utils::Hook::Set(0x57B75D, bg_weaponDefs);
		Utils::Hook::Set(0x57B809, bg_weaponDefs);
		Utils::Hook::Set(0x57B8D3, bg_weaponDefs);
		Utils::Hook::Set(0x57B96D, bg_weaponDefs);
		Utils::Hook::Set(0x57BA32, bg_weaponDefs);

		static int bg_weapClips[WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4B3603, sizeof(bg_weapClips));
		Utils::Hook::Set(0x4B360A, bg_weapClips);
		Utils::Hook::Set(0x4B3666, bg_weapClips);
		Utils::Hook::Set(0x57B993, bg_weapClips);
		Utils::Hook::Set(0x57B9E1, bg_weapClips);
		Utils::Hook::Set(0x57B9EA, bg_weapClips);

		static int bg_sharedAmmoCaps[WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4B3614, sizeof(bg_sharedAmmoCaps));
		Utils::Hook::Set(0x414D27, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x4B361B, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x4B365B, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B83B, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B870, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B87D, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B89C, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B8E0, bg_sharedAmmoCaps);
		Utils::Hook::Set(0x57B901, bg_sharedAmmoCaps);

		static int bg_weapAmmoTypes[WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4B3625, sizeof(bg_weapAmmoTypes));
		Utils::Hook::Set(0x4B362C, bg_weapAmmoTypes);
		Utils::Hook::Set(0x4B3650, bg_weapAmmoTypes);
		Utils::Hook::Set(0x57B783, bg_weapAmmoTypes);
		Utils::Hook::Set(0x57B7D1, bg_weapAmmoTypes);
		Utils::Hook::Set(0x57B7DA, bg_weapAmmoTypes);

		static int weaponStrings[WEAPON_LIMIT * 2]; // string + hash
		Utils::Hook::Set<DWORD>(0x504E01, sizeof(weaponStrings));
		Utils::Hook::Set<DWORD>(0x4C77DC, sizeof(weaponStrings));
		Utils::Hook::Set(0x4B72DC, weaponStrings);
		Utils::Hook::Set(0x4C77E2, weaponStrings);
		Utils::Hook::Set(0x504E08, weaponStrings);
		Utils::Hook::Set(0x795584, weaponStrings);
		Utils::Hook::Set(0x7955FC, weaponStrings);
		Utils::Hook::Set(0x4B72E8, &weaponStrings[1]);

		static char cg_weaponsArray[32 * WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4E3300, sizeof(cg_weaponsArray));
		Utils::Hook::Set<DWORD>(0x4E3305, sizeof(cg_weaponsArray));
		Utils::Hook::Set<DWORD>(0x4F1927, sizeof(cg_weaponsArray));
		Utils::Hook::Set<DWORD>(0x4F192C, sizeof(cg_weaponsArray));
		Utils::Hook::Set(0x4172D8, cg_weaponsArray);
		Utils::Hook::Set(0x45C96F, cg_weaponsArray);
		Utils::Hook::Set(0x45C9C7, cg_weaponsArray);
		Utils::Hook::Set(0x47F417, cg_weaponsArray);
		Utils::Hook::Set(0x4BA571, cg_weaponsArray);
		Utils::Hook::Set(0x4E330B, cg_weaponsArray);
		Utils::Hook::Set(0x4EF56C, cg_weaponsArray);
		Utils::Hook::Set(0x4F1934, cg_weaponsArray);
		Utils::Hook::Set(0x58B879, cg_weaponsArray);
		Utils::Hook::Set(0x58B98A, cg_weaponsArray);
		Utils::Hook::Set(0x58CCF7, cg_weaponsArray);
		Utils::Hook::Set(0x59BF05, cg_weaponsArray);
		Utils::Hook::Set(0x59C39B, cg_weaponsArray);
		Utils::Hook::Set(0x446D30, &cg_weaponsArray[8]);
		Utils::Hook::Set(0x59BD68, &cg_weaponsArray[13]);
		Utils::Hook::Set(0x58D0AE, &cg_weaponsArray[20]);

		static int cg_weaponsStaticArray[3 * WEAPON_LIMIT];
		Utils::Hook::Set<DWORD>(0x4E3322, sizeof(cg_weaponsStaticArray));
		Utils::Hook::Set<DWORD>(0x4F1912, sizeof(cg_weaponsStaticArray));
		Utils::Hook::Set(0x4548DE, cg_weaponsStaticArray);
		Utils::Hook::Set(0x4E3328, cg_weaponsStaticArray);
		Utils::Hook::Set(0x4EF57A, cg_weaponsStaticArray);
		Utils::Hook::Set(0x4F1919, cg_weaponsStaticArray);
		Utils::Hook::Set(0x59C095, cg_weaponsStaticArray);
		Utils::Hook::Set(0x59C09D, cg_weaponsStaticArray);

		static int unknownMaterialArray[WEAPON_LIMIT];
		Utils::Hook::Set(0x4EF619, unknownMaterialArray);
		Utils::Hook::Set(0x5896AB, unknownMaterialArray);

		// Has to do with fx, but somehow lies within the material array
		//Utils::Hook::Set(0x402069, unknownArray);
		//Utils::Hook::Set(0x4E05D9, unknownArray);

		// Patch bg_weaponDefs on the stack
		Utils::Hook::Set<DWORD>(0x40C31D, sizeof(bg_weaponDefs));
		Utils::Hook::Set<DWORD>(0x40C32F, sizeof(bg_weaponDefs));
		Utils::Hook::Set<DWORD>(0x40C311, 0x258C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C45F, 0x258C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C478, 0x258C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C434, 0x258C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C434, 0x258C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		// Move second buffer pointers
		Utils::Hook::Set<DWORD>(0x40C336, 0x12E4 + ((sizeof(bg_weaponDefs)) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x40C3C6, 0x12DC + ((sizeof(bg_weaponDefs)) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x40C3CE, 0x12DC + ((sizeof(bg_weaponDefs)) - (1200 * 4)));
		// Move arg0 pointers
		Utils::Hook::Set<DWORD>(0x40C365, 0x259C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C44E, 0x259C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		Utils::Hook::Set<DWORD>(0x40C467, 0x259C + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));
		// Move arg4 pointers
		Utils::Hook::Set<DWORD>(0x40C344, 0x25B4 + ((sizeof(bg_weaponDefs) * 2) - (1200 * 4 * 2)));

		// Patch bg_sharedAmmoCaps on the stack
		Utils::Hook::Set<DWORD>(0x4F76E6, sizeof(bg_sharedAmmoCaps));
		Utils::Hook::Set<DWORD>(0x4F7621, 0x12C8 + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x4F76AF, 0x12C8 + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x4F76DA, 0x12C8 + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x4F77C5, 0x12C8 + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		// Move arg0 pointers
		Utils::Hook::Set<DWORD>(0x4F766D, 0x12DC + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x4F76B7, 0x12DC + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		Utils::Hook::Set<DWORD>(0x4F76FB, 0x12EC + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
		// Move arg4 pointers
		Utils::Hook::Set<DWORD>(0x4F7630, 0x12DC + (sizeof(bg_sharedAmmoCaps) - (1200 * 4)));
	}

	Weapon::Weapon()
	{
		Weapon::PatchLimit();
		//Weapon::PatchConfigStrings();

		// Intercept weapon loading
		AssetHandler::OnFind(Game::XAssetType::ASSET_TYPE_WEAPON, Weapon::WeaponFileLoad);

		// weapon asset existence check
		Utils::Hook::Nop(0x408228, 5); // find asset header
		Utils::Hook::Nop(0x408230, 5); // is asset default
		Utils::Hook::Nop(0x40823A, 2); // jump

		// Skip double loading for fs_game
		Utils::Hook::Set<BYTE>(0x4081FD, 0xEB);
	}
}
