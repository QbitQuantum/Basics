void CCredits::AddCredits()
{
	// Sanity checks...

	if (!m_pClientDE) return;


	// Set the static info...

	if (!CCredit::SetStaticInfo(m_pClientDE, GetMode(), IsClearingScreen()))
	{
		return;
	}


	// Get the credits text buffer...

	char* sName = NULL;

#ifdef _ADDON
	if (IsIntro()) sName = "INTRO_AO";
	else sName = "CREDITS_AO";
#else
	if (IsIntro()) sName = "INTRO";
	else sName = "CREDITS";
#endif

	void* hModule = NULL;
	m_pClientDE->GetEngineHook("cres_hinstance", &hModule);

	char* sBuf = CreditsWin_GetTextBuffer(sName, hModule);
	if (!sBuf) return;


	char sCredit[1024];
	int  i = 0;

	while (*sBuf)
	{

		if (*sBuf == '#' && *((char*)_mbsinc((const unsigned char*)sBuf)) == '#')
		{
			sCredit[i] = '\0';

			if (_mbsnbcmp((const unsigned char*)sCredit, (const unsigned char*)">END", 4) == 0)	// end?
			{
				return;
			}

			AddCredit(sCredit);
			i = 0;

			sBuf = (char*)_mbsinc((const unsigned char*)sBuf);
			sBuf = (char*)_mbsinc((const unsigned char*)sBuf);

			while (*sBuf != '\0' && ((*sBuf == '\n') || (*sBuf == '\r'))) sBuf++;
		}
		else
		{
			int nCount = _mbsnbcnt((const unsigned char*)sBuf,1);
			memcpy(&sCredit[i], sBuf, nCount);
			i += nCount;
			sBuf = (char*)_mbsinc((const unsigned char*)sBuf);
		}
	}
}