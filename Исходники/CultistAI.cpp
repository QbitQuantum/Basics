void CultistAI::PostPropRead(ObjectCreateStruct *pStruct)
{
	CServerDE* pServerDE = GetServerDE();
	if (!pServerDE || !pStruct) return;

	char* pFilename= DNULL;
	char* pSkin = DNULL;


	if (m_bClownSkin)
	{
		pFilename = "Models\\Enemies\\m_Cultist1.abc";
		m_bMale   = DTRUE;

		switch(pServerDE->IntRandom(1,3))
		{
			case 1:		pSkin = "Skins_ao\\Enemies_ao\\m_Cultist4.dtx";	break;
			case 2:		pSkin = "Skins_ao\\Enemies_ao\\m_Cultist5.dtx";	break;
			case 3:		pSkin = "Skins_ao\\Enemies_ao\\m_Cultist6.dtx";	break;
		}
	}
	else if (m_bRobeSkin)
	{
		pFilename = "Models_ao\\Enemies_ao\\oldschool.abc";
		pSkin     = "Skins_ao\\Enemies_ao\\oldschool.dtx";
		m_bMale   = DTRUE;
	}
	else if (m_bMale)
	{
		pFilename = "Models\\Enemies\\m_Cultist1.abc";

		switch(pServerDE->IntRandom(1,3))
		{
			case 1:		pSkin = "Skins\\Enemies\\m_Cultist1.dtx";	break;
			case 2:		pSkin = "Skins\\Enemies\\m_Cultist2.dtx";	break;
			case 3:		pSkin = "Skins\\Enemies\\m_Cultist3.dtx";	break;
		}
	}
	else
	{
		pFilename = "Models\\Enemies\\f_Cultist1.abc";

		switch(pServerDE->IntRandom(1,3))
		{
			case 1:		pSkin = "Skins\\Enemies\\f_Cultist1.dtx";	break;
			case 2:		pSkin = "Skins\\Enemies\\f_Cultist2.dtx";	break;
			case 3:		pSkin = "Skins\\Enemies\\f_Cultist3.dtx";	break;
		}
	}

	_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)pFilename);
	_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)pSkin);
}