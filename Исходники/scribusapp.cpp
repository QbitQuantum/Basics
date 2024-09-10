QStringList ScribusQApp::getLang(QString lang)
{
	QStringList langs;

	// read the locales
	if (!lang.isEmpty())
		langs.push_back(lang);

	//add in user preferences lang, only overridden by lang command line option
	QString Pff = QDir::toNativeSeparators(ScPaths::getApplicationDataDir());
	QFileInfo Pffi = QFileInfo(Pff);
	if (Pffi.exists())
	{
		QString PrefsPfad;
		if (Pffi.isDir())
			PrefsPfad = Pff;
		else
			PrefsPfad = QDir::homePath();
		QString prefsXMLFile=QDir::toNativeSeparators(PrefsPfad + "/prefs140.xml");
		QFileInfo infoPrefsFile(prefsXMLFile);
		if (infoPrefsFile.exists())
		{
			PrefsFile* prefsFile = new PrefsFile(prefsXMLFile);
			if (prefsFile) {
				PrefsContext* userprefsContext = prefsFile->getContext("user_preferences");
				if (userprefsContext) {
					QString prefslang = userprefsContext->get("gui_language","");
					if (!prefslang.isEmpty())
						langs.push_back(prefslang);
				}
			}
			delete prefsFile;
		}
	}

	if (!(lang = ::getenv("LC_ALL")).isEmpty())
		langs.push_back(lang);
	if (!(lang = ::getenv("LC_MESSAGES")).isEmpty())
		langs.push_back(lang);
	if (!(lang = ::getenv("LANG")).isEmpty())
		langs.push_back(lang);

#if defined(_WIN32)
	wchar_t out[256];
	QString language, sublanguage;
	LCID lcIdo = GetUserDefaultLCID();
	WORD sortId = SORTIDFROMLCID(lcIdo);
	LANGID langId = GetUserDefaultUILanguage();
	LCID lcIdn = MAKELCID(langId, sortId);
	if ( GetLocaleInfoW(lcIdn, LOCALE_SISO639LANGNAME , out, 255) )
	{
		language = QString::fromUtf16( (ushort*)out );
		if ( GetLocaleInfoW(lcIdn, LOCALE_SISO3166CTRYNAME, out, 255) )
		{
			sublanguage = QString::fromUtf16( (ushort*)out ).toLower();
			lang = language;
			if ( sublanguage != language && !sublanguage.isEmpty() )
				lang += "_" + sublanguage.toUpper();
			langs.push_back(lang);
		}
	}
#endif

	langs.push_back(QString(QLocale::system().name()));

	// remove duplicate entries...
	QStringList::Iterator it = langs.end();
	while (it != langs.begin())
	{
		--it;
		if (langs.count(*it) > 1)
			it = langs.erase(it);
	}

	return langs;
}