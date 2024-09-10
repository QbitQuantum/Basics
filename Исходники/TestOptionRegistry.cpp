void TestOptionRegistry::setUpSuite()
{
	if(RegUtils::IsRegKeyPresent(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1")))
	{
		assertTest(RegUtils::RecursiveDeleteKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1")));
	}
	if(RegUtils::IsRegKeyPresent(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3")))
	{
		assertTest(RegUtils::RecursiveDeleteKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3")));
	}

	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1")));
	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1")));
	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory2")));
	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory2\\TestCategory2Sub3")));
	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3")));
	assertTest(RegUtils::CreateKey(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3\\TestCategory3Sub2")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory2\\TestCategory2Sub3"), _T("RegSzStringValue"), _T("This is a Registry test string value")));

	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3\\TestCategory3Sub2"), _T("RegSzIntValue"), _T("-7")));
	assertTest(RegUtils::SetRegDWORDValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory3\\TestCategory3Sub2"), _T("RegDWordIntValue"), 235));

	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBoolTrue"), _T("True")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBoolFalse"), _T("False")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBooltrueLowerCase"), _T("true")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBoolfalseLowerCase"), _T("false")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBool1"), _T("1")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBool0"), _T("0")));
	assertTest(RegUtils::SetRegDWORDValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegDWordBool1"), 1));
	assertTest(RegUtils::SetRegDWORDValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegDWordBool0"), 0));
	assertTest(RegUtils::SetRegDWORDValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegDWordBoolNon1Or0"), 5));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBoolSomeString"), _T("This a string")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("RegSzBoolSomeNumber"), _T("234")));

	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("ThisStringOptionDoesNotExist"), _T("It exists in the registry but not in the default map file")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("ThisIntOptionDoesNotExist"), _T("-457")));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), _T("ThisBoolOptionDoesNotExist"), _T("1")));

	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), ToUnicode(std::string("название-имя")).GetString(), ToUnicode(std::string("Мир языков")).GetString()));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), ToUnicode(std::string("名字")).GetString(), ToUnicode(std::string("世界多语言")).GetString()));
	assertTest(RegUtils::SetRegStringValue(HKEY_CURRENT_USER, OPTION_REG_LOCATION _T("\\TestCategory1\\TestCategory1Sub1"), ToUnicode(std::string("Русский")).GetString(), ToUnicode(std::string("<имет>")).GetString()));
}