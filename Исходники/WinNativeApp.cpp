StringTable::LangId NativeApp::RAD_IMPLEMENT_GET(systemLangId) {
	StringTable::LangId id = StringTable::LangId_EN;
	
	LANGID winId = GetUserDefaultUILanguage();
	
	switch (winId&0xff) {
		case LANG_CHINESE:
			id = StringTable::LangId_CH;
			break;
		case LANG_FRENCH:
			id = StringTable::LangId_FR;
			break;
		case LANG_GERMAN:
			id = StringTable::LangId_GR;
			break;
		case LANG_ITALIAN:
			id = StringTable::LangId_IT;
			break;
		case LANG_JAPANESE:
			id = StringTable::LangId_JP;
			break;
		case LANG_RUSSIAN:
		case LANG_UKRAINIAN:
			id = StringTable::LangId_RU;
			break;
		case LANG_SPANISH:
			id = StringTable::LangId_SP;
			break;
		default:
			break;
	}
	
	return id;
}