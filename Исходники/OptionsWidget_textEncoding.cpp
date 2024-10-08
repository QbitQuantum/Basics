OptionsWidget_textEncoding::OptionsWidget_textEncoding(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("textencoding_options_widget");
	createLayout();

	KviTalGroupBox * gbox = addGroupBox(0, 0, 0, 0, Qt::Horizontal, __tr2qs_ctx("Encoding", "options"));
	QGridLayout * grid = new QGridLayout;
	gbox->setLayout(grid);

	//server encoding
	grid->addWidget(addLabel(gbox, __tr2qs_ctx("Default server encoding:", "options")), 0, 0);

	m_pSrvEncodingCombo = new QComboBox(gbox);
	grid->addWidget(m_pSrvEncodingCombo, 0, 1);

	m_pSrvEncodingCombo->addItem(__tr2qs_ctx("Use Language Encoding", "options"));

	//text encoding
	grid->addWidget(addLabel(gbox, __tr2qs_ctx("Default text encoding:", "options")), 1, 0);

	m_pTextEncodingCombo = new QComboBox(gbox);
	grid->addWidget(m_pTextEncodingCombo, 1, 1);

	m_pTextEncodingCombo->addItem(__tr2qs_ctx("Use Language Encoding", "options"));

	//common between text and server encoding
	int i = 0;
	int iTextMatch = 0, iSrvMatch = 0;
	KviLocale::EncodingDescription * d = KviLocale::instance()->encodingDescription(i);
	while(d->pcName)
	{
		if(KviQString::equalCI(d->pcName, KVI_OPTION_STRING(KviOption_stringDefaultTextEncoding)))
			iTextMatch = i + 1;
		if(KviQString::equalCI(d->pcName, KVI_OPTION_STRING(KviOption_stringDefaultSrvEncoding)))
			iSrvMatch = i + 1;

		m_pTextEncodingCombo->insertItem(m_pTextEncodingCombo->count(), d->pcName);
		m_pSrvEncodingCombo->insertItem(m_pSrvEncodingCombo->count(), d->pcName);
		i++;
		d = KviLocale::instance()->encodingDescription(i);
	}

	m_pTextEncodingCombo->setCurrentIndex(iTextMatch);
	m_pSrvEncodingCombo->setCurrentIndex(iSrvMatch);

	gbox = addGroupBox(0, 1, 0, 1, Qt::Horizontal, __tr2qs_ctx("Language", "options"));
	grid = new QGridLayout;
	gbox->setLayout(grid);

	grid->addWidget(addLabel(gbox, __tr2qs_ctx("Force language:", "options")), 0, 0);

	m_pForcedLocaleCombo = new QComboBox(gbox);

	grid->addWidget(m_pForcedLocaleCombo, 0, 1);

	grid->addWidget(addLabel(gbox, __tr2qs_ctx("<b>Note:</b> You must restart KVIrc to apply any language changes", "options")), 1, 0, 1, 2);

	m_pForcedLocaleCombo->addItem(__tr2qs_ctx("Automatic detection", "options"));
	m_pForcedLocaleCombo->addItem(__tr2qs_ctx("en", "options"));

	QString szLangFile;
	g_pApp->getLocalKvircDirectory(szLangFile, KviApplication::None, KVI_FORCE_LOCALE_FILE_NAME);

	bool bIsDefaultLocale = !KviFileUtils::fileExists(szLangFile);
	//We Have set locale, but not restarted kvirc
	if(!g_szPrevSetLocale.isEmpty())
		m_szLanguage = g_szPrevSetLocale;
	else
		m_szLanguage = KviLocale::instance()->localeName();

	QString szLocaleDir;
	g_pApp->getGlobalKvircDirectory(szLocaleDir, KviApplication::Locale);

	QStringList list = QDir(szLocaleDir).entryList(QStringList("kvirc_*.mo"), QDir::Files);

	i = 0;
	int iMatch = 0;

	for(auto szTmp : list)
	{
		szTmp.replace("kvirc_", "");
		szTmp.replace(".mo", "");
		m_pForcedLocaleCombo->insertItem(m_pForcedLocaleCombo->count(), szTmp);
		if(QString::compare(szTmp, m_szLanguage, Qt::CaseInsensitive) == 0)
			iMatch = i + 2;
		i++;
	}
	if(bIsDefaultLocale)
		m_pForcedLocaleCombo->setCurrentIndex(0);
	else if(KviQString::equalCI(m_szLanguage, "en"))
		m_pForcedLocaleCombo->setCurrentIndex(1);
	else
		m_pForcedLocaleCombo->setCurrentIndex(iMatch);

#ifdef COMPILE_ENCHANT_SUPPORT
	{
		gbox = addGroupBox(0, 2, 0, 2, Qt::Horizontal, __tr2qs_ctx("Spell Checker Dictionaries", "options"));

		KviKvsVariant availableDictionaries;
		KviKvsScript::evaluate("$spellchecker.availableDictionaries", nullptr, nullptr, &availableDictionaries);
		const KviPointerHashTable<QString, KviKvsVariant> * hashTable = availableDictionaries.hash()->dict();
		KviPointerHashTableIterator<QString, KviKvsVariant> iter(*hashTable);
		QMap<QString, QString> dictMap;
		for(bool b = iter.moveFirst(); b; b = iter.moveNext())
		{
			QString szDescription;
			iter.current()->asString(szDescription);
			dictMap[iter.currentKey()] = szDescription;
		}

		m_pSpellCheckerDictionaries = new QTableWidget(gbox);
		m_pSpellCheckerDictionaries->setRowCount(dictMap.size());
		m_pSpellCheckerDictionaries->setColumnCount(2);
		QStringList header;
		header << __tr2qs_ctx("Language Code", "options");
		header << __tr2qs_ctx("Provided by", "options");
		m_pSpellCheckerDictionaries->setHorizontalHeaderLabels(header);
		m_pSpellCheckerDictionaries->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		m_pSpellCheckerDictionaries->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_pSpellCheckerDictionaries->setSelectionMode(QAbstractItemView::SingleSelection);
		m_pSpellCheckerDictionaries->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		int row = 0;
		for(QMap<QString, QString>::iterator it = dictMap.begin(); it != dictMap.end(); ++it, ++row)
		{
			QTableWidgetItem * itemLang = new QTableWidgetItem(it.key());
			itemLang->setCheckState(KVI_OPTION_STRINGLIST(KviOption_stringlistSpellCheckerDictionaries).contains(it.key()) ? Qt::Checked : Qt::Unchecked);
			itemLang->setFlags(itemLang->flags() & ~Qt::ItemIsEditable);
			m_pSpellCheckerDictionaries->setItem(row, 0, itemLang);

			QTableWidgetItem * itemDesc = new QTableWidgetItem(it.value());
			itemDesc->setFlags(itemDesc->flags() & ~Qt::ItemIsEditable);
			m_pSpellCheckerDictionaries->setItem(row, 1, itemDesc);
		}

		m_pSpellCheckerDictionaries->resizeColumnsToContents();
		m_pSpellCheckerDictionaries->resizeRowsToContents();
	}
#else
	addRowSpacer(0, 2, 0, 2);
#endif
}