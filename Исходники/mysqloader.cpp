void MysqLoader::writeSettings()
{
	QFile autostartFile;

	LanguageTools language;

	QSettings mysqloader_conf(QSettings::NativeFormat,
							  QSettings::UserScope, APP_NAME);
	mysqloader_conf.beginGroup("MySQLoader");
	mysqloader_conf.setValue("Autostart",
							 autostartCheckBox->isChecked());
	mysqloader_conf.setValue("Desktop_Icon",
							 desktopIconCheckBox->isChecked());
	mysqloader_conf.setValue("Set_Language",
							 languageGroup->isChecked());
	mysqloader_conf.setValue("languageNiceName",
							 languageCombo->currentText());
	mysqloader_conf.setValue("languageFileName",
							 fileToNiceName->value(
								 languageCombo->currentText()));
	mysqloader_conf.setValue("Meldung",
							 showMeldungCheckBox->isChecked());
	mysqloader_conf.setValue("Meldung_App",
							 meldungAppCheckBox->isChecked());
	mysqloader_conf.setValue("Zeige_Fenster",
							 showDialogCheckBox->isChecked());
	mysqloader_conf.endGroup();

	mysqloader_conf.beginGroup("MySQL_Paths");
	mysqloader_conf.setValue("MySQL_PID_FILE",
							 pidFileEdit->text());
	mysqloader_conf.setValue("MySQL_Server",
                             mysqlEdit->text());
	mysqloader_conf.endGroup();



	if (autostartCheckBox->isChecked() == true) {
		autostartFile.copy("/usr/share/applications/mysqloader.desktop",
						   QDir::homePath() +
						   "/.config/autostart/mysqloader.desktop");
	} else {
		autostartFile.remove(QDir::homePath() +
							 "/.config/autostart/mysqloader.desktop");
	}

	if (desktopIconCheckBox->isChecked() == true) {
		autostartFile.copy("/usr/share/applications/mysqloader.desktop",
						   QDir::homePath() +
						   "/Desktop/mysqloader.desktop");
	} else {
		autostartFile.remove(QDir::homePath() +
							 "/Desktop/mysqloader.desktop");
	}
}