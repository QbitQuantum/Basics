void CMagicDamage::LogSkillList(char* Buffer, int iSize)
{
	this->Init();
	CWzMemScript WzMemScript;

	WzMemScript.SetBuffer(Buffer, iSize);

	int Token;
	int n=0;
	int number;
	char name[50];
	int requireLevel;
	int damage;
	int mana;
	int bp=0;
	int dis;
	int rEnergy;
	int iSkillType;
	int rLeadership;
	int rDelay;
	int attr;
	int iSkillUseType;
	int iSkillBrand;
	int iKillCount;
	int RequireStatus[MAX_REQ_SKILL_STATUS] = {0};
	BYTE RequireClass[MAX_TYPE_PLAYER];

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			strcpy_s(name, sizeof(name), WzMemScript.GetString() );

			Token = WzMemScript.GetToken();
			requireLevel = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			damage = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			mana = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			bp = (int)WzMemScript.GetNumber();	// Agility Gauge

			Token = WzMemScript.GetToken();
			dis = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rDelay = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rEnergy = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rLeadership = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			attr = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillType = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillUseType = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillBrand = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iKillCount = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[0] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[1] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[2] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[0] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[1] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[2] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[3] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[4] = (BYTE)WzMemScript.GetNumber();


			this->Set(name, number,damage, requireLevel, mana, bp, dis, attr, iSkillType, RequireClass, rEnergy, rLeadership, rDelay);
			this->SetEx(number, iSkillUseType, iSkillBrand, iKillCount, RequireStatus);
			DefMagicInf[number].Set(number, 0);
		}
	}

	LogAdd("(%s) Skill information data load complete", "Skill");
}