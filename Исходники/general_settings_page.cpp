void GeneralSettingsPage::apply()
{
	auto language = language_box->currentData();
	if (language != getSetting(Settings::General_Language)
	    || translation_file != getSetting(Settings::General_TranslationFile).toString())
	{
		// Show an message box in the new language.
		TranslationUtil translation((QLocale::Language)language.toInt(), translation_file);
		auto new_language = translation.getLocale().language();
		switch (new_language)
		{
		case QLocale::AnyLanguage:
		case QLocale::C:
		case QLocale::English:
			QMessageBox::information(window(), QLatin1String("Notice"), QLatin1String("The program must be restarted for the language change to take effect!"));
			break;
			
		default:
			qApp->installEventFilter(this);
			qApp->installTranslator(&translation.getQtTranslator());
			qApp->installTranslator(&translation.getAppTranslator());
			QMessageBox::information(window(), tr("Notice"), tr("The program must be restarted for the language change to take effect!"));
			qApp->removeTranslator(&translation.getAppTranslator());
			qApp->removeTranslator(&translation.getQtTranslator());
			qApp->removeEventFilter(this);
		}
		
		setSetting(Settings::General_Language, new_language);
		setSetting(Settings::General_TranslationFile, translation_file);
#if defined(Q_OS_MAC)
		// The native [file] dialogs will use the first element of the
		// AppleLanguages array in the application's .plist file -
		// and this file is also the one used by QSettings.
		const QString mapper_language(translation.getLocale().name().left(2));
		QSettings().setValue(QLatin1String{"AppleLanguages"}, { mapper_language });
#endif
	}
	
	setSetting(Settings::General_OpenMRUFile, open_mru_check->isChecked());
	setSetting(Settings::HomeScreen_TipsVisible, tips_visible_check->isChecked());
	setSetting(Settings::General_NewOcd8Implementation, ocd_importer_check->isChecked());
	setSetting(Settings::General_RetainCompatiblity, compatibility_check->isChecked());
	setSetting(Settings::General_PixelsPerInch, ppi_edit->value());
	
	auto name_latin1 = encoding_box->currentText().toLatin1();
	if (name_latin1 == "System"
	    || QTextCodec::codecForName(name_latin1))
	{
		setSetting(Settings::General_Local8BitEncoding, name_latin1);
	}
	
	int interval = autosave_interval_edit->value();
	if (!autosave_check->isChecked())
		interval = -interval;
	setSetting(Settings::General_AutosaveInterval, interval);
}