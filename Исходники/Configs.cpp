void cConfigs::LoadFixes()
{
#ifdef _GS
	//BloodCasle Time
	int bloodtime = 200 * GetPrivateProfileInt("Events","BCTimeRemain", 60, RZEvents);            *(unsigned int *) GS_BLOODREMAIN = bloodtime;                
	*(unsigned int *) GS_BLOODREMAIN2 = bloodtime;                    
	*(unsigned int *) GS_BLOODREMAIN3 = bloodtime; 
	//remain ChaosCastle:
	int iCcT = 70000 * (GetPrivateProfileIntA("Events","CCTimeRemain",30,RZEvents));
	DWORD dCcT = iCcT;
	*(unsigned int *) GS_CCTimeRemain = dCcT;
	//
	*(unsigned char*) oCcMinPlayers = GetInt(0, 6, 6,"Events","CcMinPlayers",RZEvents);
#else
//	disablecslogs		= GetInt(0, 1, 0,"Common", "DisableCSlogs", RZCGS);
#endif 
	PersonalIDFix		= GetInt(0, 1, 1, "Bypasseres", "PersonalIDBypasser", RZCommon);
	GuildIDFix			= GetInt(0, 1, 1, "Bypasseres", "GuildIDBypasser", RZCommon);
	AllowExeAnc			= GetInt(0, 1, 1, "SpecialItem", "AllowExeAnc", RZItems);	
	AllowJohAnc			= GetInt(0, 1, 1, "SpecialItem", "AllowJohAnc", RZItems);
	AllowExeSock		= GetInt(0, 1, 1, "SpecialItem", "AllowExeSock", RZItems);
	MaxLifeOpt			= GetInt(0, 1, 1, "SpecialItem", "MaxLifeOpt", RZItems);
	FixPotionsMax		= GetInt(0, 1, 1, "Common", "Use255potions", RZItems);

	*(unsigned char*) GS_SOUL_RATE_NORMAL = GetChar(0,100,60,"JewelRates","SoulSuccessRateNormal",RZItems);
	*(unsigned char*) GS_SOUL_RATE_SPECIAL = GetChar(0,100,50,"JewelRates","SoulSuccessRateSpecial",RZItems);
	*(unsigned char*) GS_SOUL_RATE_SOCKET = GetChar(0,100,40,"JewelRates","SoulSuccessRateSocket",RZItems);
	*(unsigned char*) GS_SOUL_LUCK_ADD = GetChar(0,100,20,"JewelRates","SoulSuccessRateLuck",RZItems);
	*(unsigned char*) GS_JOL_FAIL_RATE = GetChar(0,100,50,"JewelRates","LifeFailRate",RZItems);

}