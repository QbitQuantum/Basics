void CPreferences::InitThreadLocale()
{
	ASSERT( m_wLanguageID != 0 );

	// NOTE: This function is for testing multi language support only.
	// NOTE: This function is *NOT* to be enabled in release builds nor to be offered by any Mod!
	if (theApp.GetProfileInt(_T("eMule"), _T("SetLanguageACP"), 0) != 0)
	{
		//LCID lcidUser = GetUserDefaultLCID();		// Installation, or altered by user in control panel (WinXP)

		// get the ANSI codepage which is to be used for all non-Unicode conversions.
		LANGID lidSystem = m_wLanguageID;

		// get user's sorting preferences
		//UINT uSortIdUser = SORTIDFROMLCID(lcidUser);
		//UINT uSortVerUser = SORTVERSIONFROMLCID(lcidUser);
		// we can't use the same sorting paramters for 2 different Languages..
		UINT uSortIdUser = SORT_DEFAULT;
		UINT uSortVerUser = 0;

		// set thread locale, this is used for:
		//	- MBCS->Unicode conversions (e.g. search results).
		//	- Unicode->MBCS conversions (e.g. publishing local files (names) in network, or savint text files on local disk)...
		LCID lcid = MAKESORTLCID(lidSystem, uSortIdUser, uSortVerUser);
		SetThreadLocale(lcid);

		// if we set the thread locale (see comments above) we also have to specify the proper
		// codepage for the C-RTL, otherwise we may not be able to store some strings as MBCS
		// (Unicode->MBCS conversion may fail)
		SetRtlLocale(lcid);
	}
	else if (theApp.GetProfileInt(_T("eMule"), _T("SetSystemACP"), 0) != 0)
	{
		LCID lcidSystem = GetSystemDefaultLCID();	// Installation, or altered by user in control panel (WinXP)
		//LCID lcidUser = GetUserDefaultLCID();		// Installation, or altered by user in control panel (WinXP)

		// get the ANSI codepage which is to be used for all non-Unicode conversions.
		LANGID lidSystem = LANGIDFROMLCID(lcidSystem);

		// get user's sorting preferences
		//UINT uSortIdUser = SORTIDFROMLCID(lcidUser);
		//UINT uSortVerUser = SORTVERSIONFROMLCID(lcidUser);
		// we can't use the same sorting paramters for 2 different Languages..
		UINT uSortIdUser = SORT_DEFAULT;
		UINT uSortVerUser = 0;

		// create a thread locale which gives full backward compability for users which had run ANSI emule on 
		// a system where the system's code page did not match the user's language..
		LCID lcid = MAKESORTLCID(lidSystem, uSortIdUser, uSortVerUser);
		LCID lcidThread = GetThreadLocale();
		if (lcidThread != lcid)
		{
			TRACE("+++ Setting thread locale: 0x%08x\n", lcid);
			SetThreadLocale(lcid);

			// if we set the thread locale (see comments above) we also have to specify the proper
			// codepage for the C-RTL, otherwise we may not be able to store some strings as MBCS
			// (Unicode->MBCS conversion may fail)
			SetRtlLocale(lcid);
		}
	}
}