void  XAP_Win32EncodingManager::initialize()
{
	char szLocaleInfo[64];
	static char szCodepage[64];
	static char szSystemCodepage[64];
	static char szLanguage[64];
	static char szTerritory[64];

	NativeNonUnicodeEncodingName = Native8BitEncodingName = NativeSystemEncodingName = NativeEncodingName = "CP1252";
	LanguageISOName = "en";
	LanguageISOTerritory = NULL;

	XAP_EncodingManager::initialize();

	// Unicode Encoding Name
	// TODO Does NT use UCS-2BE internally on non-Intel CPUs?
	// TODO Windows 2000 and XP use UTF-16 but on 2000 it may involve a
	// TODO  registry setting
	NativeUnicodeEncodingName = getUCS2LEName();

	// Encodings
	// User Encoding (Set via Region/Locale; does not require reboot)
	if (GetLocaleInfoA(LOCALE_USER_DEFAULT,LOCALE_IDEFAULTANSICODEPAGE,szLocaleInfo,sizeof(szLocaleInfo)/sizeof(szLocaleInfo[0])))
	{
		// Windows Unicode locale?
		if (!strcmp(szLocaleInfo,"0"))
		{
			NativeEncodingName = NativeUnicodeEncodingName;
			m_bIsUnicodeLocale = true;
		}
		else
		{
			szCodepage[0] = 'C';
			szCodepage[1] = 'P';
			strcpy(szCodepage+2,szLocaleInfo);
			NativeNonUnicodeEncodingName = Native8BitEncodingName = NativeEncodingName = szCodepage;
			m_bIsUnicodeLocale = false;
		}
	}
	// System Encoding (Used by GUI,DOS; Set via Region/Default Language; requires reboot)
	if (GetLocaleInfoA(LOCALE_SYSTEM_DEFAULT,LOCALE_IDEFAULTANSICODEPAGE,szLocaleInfo,sizeof(szLocaleInfo)/sizeof(szLocaleInfo[0])))
	{
		// Windows Unicode locale?
		if (!strcmp(szLocaleInfo,"0"))
		{
			NativeSystemEncodingName = NativeUnicodeEncodingName;
			//m_bIsUnicodeLocale = true;
		}
		else
		{
			szSystemCodepage[0] = 'C';
			szSystemCodepage[1] = 'P';
			strcpy(szSystemCodepage+2,szLocaleInfo);
			NativeSystemEncodingName = szSystemCodepage;
			//m_bIsUnicodeLocale = false;
		}
	}

    m_bIsUnicodeLocale = true;
	NativeEncodingName = "UCS-2LE";	
	NativeSystemEncodingName = "UCS-2LE";

	if (UT_getISO639Language(szLanguage))
	{
		LanguageISOName = szLanguage;
	}
	else
	{
		UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
	}
	if (UT_getISO3166Country(szTerritory))
	{
		LanguageISOTerritory = szTerritory;
	}

	describe();
}