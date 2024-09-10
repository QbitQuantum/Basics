KviLocale::KviLocale(QApplication * pApp, const QString & szLocaleDir, const QString & szForceLocaleDir)
{
	m_pApp = pApp;

	// first of all try to find out the current locale
	QString szLangFile = QString("%1/%2").arg(szForceLocaleDir, KVI_FORCE_LOCALE_FILE_NAME);

	if(KviFileUtils::fileExists(szLangFile))
		KviFileUtils::readFile(szLangFile, g_szLang);
	if(g_szLang.isEmpty())
		g_szLang = KviEnvironment::getVariable("KVIRC_LANG");
#ifdef COMPILE_KDE_SUPPORT
	if(g_szLang.isEmpty())
		g_szLang = KviEnvironment::getVariable("KDE_LANG");
#endif //COMPILE_KDE_SUPPORT
	if(g_szLang.isEmpty())
		g_szLang = KviEnvironment::getVariable("LC_MESSAGES");
	if(g_szLang.isEmpty())
		g_szLang = KviEnvironment::getVariable("LANG");
	if(g_szLang.isEmpty())
		g_szLang = QLocale::system().name();
	if(g_szLang.isEmpty())
		g_szLang = "en";
	g_szLang = g_szLang.trimmed();

	g_szDefaultLocalePath = szLocaleDir;

	// the main catalogue is supposed to be kvirc_<language>.mo
	g_pMainCatalogue = new KviMessageCatalogue();
	// the catalogue dict
	g_pCatalogueDict = new KviPointerHashTable<const char *, KviMessageCatalogue>;
	g_pCatalogueDict->setAutoDelete(true);

	// the smart codec dict
	g_pSmartCodecDict = new KviPointerHashTable<const char *, KviSmartTextCodec>;
	// the Qt docs explicitly state that we shouldn't delete
	// the codecs by ourselves...
	g_pSmartCodecDict->setAutoDelete(false);

	if(!g_szLang.isEmpty())
	{
		// ensure Qt will use the right locale when formatting dates, numbers, ..
		// Note: Qt will use the system() locale anyway, we need to construct an empty QLocale()
		// to get it use our specified locale.
		QLocale::setDefault(QLocale(g_szLang));

		QString szBuffer;
		if(findCatalogue(szBuffer, "kvirc", szLocaleDir))
		{
			g_pMainCatalogue->load(szBuffer);
			g_pTranslator = new KviTranslator(m_pApp);
			m_pApp->installTranslator(g_pTranslator);
		}
		else
		{
			KviCString szTmp = g_szLang;
			szTmp.cutFromFirst('.');
			szTmp.cutFromFirst('_');
			szTmp.cutFromFirst('@');
			szTmp.toLower();
			if(!(kvi_strEqualCI(szTmp.ptr(), "en") || kvi_strEqualCI(szTmp.ptr(), "c") || kvi_strEqualCI(szTmp.ptr(), "us") || kvi_strEqualCI(szTmp.ptr(), "gb") || kvi_strEqualCI(szTmp.ptr(), "posix")))
			{
				// FIXME: THIS IS NO LONGER VALID!!!
				qDebug("Can't find the catalogue for locale \"%s\" (%s)", g_szLang.toUtf8().data(), szTmp.ptr());
				qDebug("There is no such translation or the $LANG variable was incorrectly set");
				qDebug("You can use $KVIRC_LANG to override the catalogue name");
				qDebug("For example you can set KVIRC_LANG to it_IT to force usage of the it.mo catalogue");
			}
		}
	}
}