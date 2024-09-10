const vector<string>& CCobUnitScriptNames::GetScriptNames()
{
	static vector<string> scriptNames;

	if (!scriptNames.empty()) {
		return scriptNames;
	}

	scriptNames.resize(COBFN_Last + (MAX_WEAPONS_PER_UNIT * COBFN_Weapon_Funcs));

	scriptNames[COBFN_Create]        = "Create";
	scriptNames[COBFN_Destroy]       = "Destroy";
	scriptNames[COBFN_StartMoving]   = "StartMoving";
	scriptNames[COBFN_StopMoving]    = "StopMoving";
	scriptNames[COBFN_Activate]      = "Activate";
	scriptNames[COBFN_Killed]        = "Killed";
	scriptNames[COBFN_Deactivate]    = "Deactivate";
	scriptNames[COBFN_SetDirection]  = "SetDirection";
	scriptNames[COBFN_SetSpeed]      = "SetSpeed";
	scriptNames[COBFN_RockUnit]      = "RockUnit";
	scriptNames[COBFN_HitByWeapon]   = "HitByWeapon";
	scriptNames[COBFN_MoveRate0]     = "MoveRate0";
	scriptNames[COBFN_MoveRate1]     = "MoveRate1";
	scriptNames[COBFN_MoveRate2]     = "MoveRate2";
	scriptNames[COBFN_MoveRate3]     = "MoveRate3";
	scriptNames[COBFN_SetSFXOccupy]  = "setSFXoccupy";
	scriptNames[COBFN_HitByWeaponId] = "HitByWeaponId";

	scriptNames[COBFN_QueryLandingPadCount] = "QueryLandingPadCount";
	scriptNames[COBFN_QueryLandingPad]      = "QueryLandingPad";
	scriptNames[COBFN_Falling]              = "Falling";
	scriptNames[COBFN_Landed]               = "Landed";
	scriptNames[COBFN_BeginTransport]       = "BeginTransport";
	scriptNames[COBFN_QueryTransport]       = "QueryTransport";
	scriptNames[COBFN_TransportPickup]      = "TransportPickup";
	scriptNames[COBFN_StartUnload]          = "StartUnload";
	scriptNames[COBFN_EndTransport]         = "EndTransport";
	scriptNames[COBFN_TransportDrop]        = "TransportDrop";
	scriptNames[COBFN_SetMaxReloadTime]     = "SetMaxReloadTime";
	scriptNames[COBFN_StartBuilding]        = "StartBuilding";
	scriptNames[COBFN_StopBuilding]         = "StopBuilding";
	scriptNames[COBFN_QueryNanoPiece]       = "QueryNanoPiece";
	scriptNames[COBFN_QueryBuildInfo]       = "QueryBuildInfo";
	scriptNames[COBFN_Go]                   = "Go";

	// Also add the weapon aiming stuff
	for (int i = 0; i < MAX_WEAPONS_PER_UNIT; ++i) {
		char buf[15];
		sprintf(buf, "Weapon%d", i + 1);
		string weapon(buf);
		sprintf(buf, "%d", i + 1);
		string weapnum(buf);
		const int n = COBFN_Weapon_Funcs * i;
		scriptNames[COBFN_QueryPrimary   + n] = "Query"   + weapon;
		scriptNames[COBFN_AimPrimary     + n] = "Aim"     + weapon;
		scriptNames[COBFN_AimFromPrimary + n] = "AimFrom" + weapon;
		scriptNames[COBFN_FirePrimary    + n] = "Fire"    + weapon;
		scriptNames[COBFN_EndBurst       + n] = "EndBurst"     + weapnum;
		scriptNames[COBFN_Shot           + n] = "Shot"         + weapnum;
		scriptNames[COBFN_BlockShot      + n] = "BlockShot"    + weapnum;
		scriptNames[COBFN_TargetWeight   + n] = "TargetWeight" + weapnum;
	}

	//for (size_t i = 0; i < scriptNames.size(); ++i) {
	//	logOutput.Print("COBFN: %3d %s", i, scriptNames[i].c_str());
	//}

	return scriptNames;
}