void ImportConfig::on_cmdImport_clicked()
{
    if (!m_ui->txtExistingOvpn->text().isEmpty()) {
        // Import existing file
        QString configName (m_ui->txtExistingOvpn->text().replace(".ovpn", ""));
        configName = configName.right(configName.size() - configName.lastIndexOf("/") - 1);

        // Anderer name als Dateiname
        if (m_ui->rbSaveAsName->isChecked()) {
            if (!m_ui->txtNewName->text().isEmpty()) {
                configName = m_ui->txtNewName->text();
            }
        }

        QString pathToConfig (m_ui->txtExistingOvpn->text());
        // Copy config to local app data and rename it, if an other name is specified
        // Only in service mode!
        if(!Settings::getInstance()->getIsPortableClient()) {

            // If file is available copy it
            // First create folder
            QString newConfigFolderPath (QString("%1/config/%2")
                                         .arg(AppFunc::getAppSavePath())
                                         .arg(configName));
            QDir newConfigFolderPathDirectory (newConfigFolderPath);
            if (newConfigFolderPathDirectory.exists(newConfigFolderPath)){
                // A config with this name is already existing
                Message::error(QObject::tr("A configuration with this name is already existing!"));
                //
                return;
            }

            // Create path
            newConfigFolderPathDirectory.mkpath(newConfigFolderPath);

            // Now copy Files
            QString newConfigPath (QString("%1/%2.ovpn")
                                   .arg(newConfigFolderPath)
                                   .arg(configName));

            QFile::copy(pathToConfig, newConfigPath);
            //
            QString sourceDirectory (pathToConfig.left(pathToConfig.lastIndexOf("/")));
            //
            // Override old path
            pathToConfig = newConfigPath;
            // Ca

			auto copyConfigFile = [&](const QString &key)
			{
				auto keyValue = (ConfigValues::instance()->valueFromConfigKey(pathToConfig, key));

				if(!keyValue.isEmpty())
				{
					QString sourcePath (QString("%1/%2")
						.arg(sourceDirectory)
						.arg(keyValue));

					QString destName (keyValue);

					if (ConfigValues::instance()->isGivenPathAbsolute(keyValue)) {
						// Yes, override path
						sourcePath = keyValue;
						// Get the file name from path
						destName = ConfigValues::instance()->fileNameOfAbsolutePath(keyValue);
						// Change value in config
						ConfigValues::instance()->changeKeyValueInConfig(pathToConfig, key, QString("\"%1\"")
							.arg(destName));
					}
					// Copy
					QFile::copy(sourcePath, QString("%1/%2")
						.arg(newConfigFolderPath)
						.arg(destName));
				}
			};

			for(const auto &key : keys)
			{
				copyConfigFile(key);
			}
        }

        Preferences::instance()->addNewConfigToDatabase(configName, pathToConfig);
        Preferences::instance()->refreshConfigList();
        Preferences::instance()->setConnectionStatus();
        Preferences::instance()->setIcon();

        // Fertig
        Message::information(QObject::tr("Import successfully ended!"), QObject::tr("Import Configuration"));
        Preferences::instance()->refreshDialog();
        this->close();
    } else {
        // Import crypt file
        if (m_ui->txtPassword->text().isEmpty()) {
            Message::error(QObject::tr("No password specified!"), QObject::tr("Import Configuration"));
            return;
        }
        if (!m_ui->txtImportPath->text().isEmpty()) {
            if (m_ui->rbSaveAsName->isChecked() && m_ui->txtNewName->text().isEmpty()) {
                Message::error(QObject::tr("No import name specified!"), QObject::tr("Import Configuration"));
                return;
            }

            // Portale oder install
            QString dirPath;
            QString configName;

            if (!m_ui->rbSaveAsName->isChecked()) {
                configName = m_ui->txtImportPath->text().right(m_ui->txtImportPath->text().size() - m_ui->txtImportPath->text().lastIndexOf("/") -1);
                configName = configName.left(configName.size()-6);
            } else {
                configName = m_ui->txtNewName->text().trimmed();
            }

            dirPath = AppFunc::getAppSavePath() + QString ("/config/") + configName;

            // Verzeichnis da?
            QDir dirobj (dirPath);
            if (!dirobj.exists(dirPath)){
                //Verzeichnis existiert nicht
                // Pfad erstellen
                if (!dirobj.mkpath(dirPath)) {
                    // Pfad konnte nicht erstellt werden
                    Message::error(QObject::tr("Unable to create directory!"), QObject::tr("Import Configuration"));
                    return;
                }
            } else {
                // Verzeichnis existiert
                Message::error(QObject::tr("A diretory with this name already exists!"), QObject::tr("Import Configuration"));
                return;
            }
            // Datei ins neue Verzeichnis kopieren
            //QFile importFileCrypt (m_ui->txtImportPath->text());
            QString packFile = dirPath + QString("/") + configName + QString(".zip");

            // Erstmal entschlüsseln
            if(QFile::exists(packFile)) {
                QFile::remove(packFile);
            }

            // Die Daten einlesen
            {
                QFile crypted (m_ui->txtImportPath->text());
                if (crypted.open(QIODevice::ReadOnly)) {
                    // Nun das Ziel öfffnen
                    QFile targetFile (packFile);
                    if (targetFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                        // Alles offen, kann losgehen
                        QByteArray data = crypted.readAll();
                        Crypt crypt;
                        crypt.setSecretKey(m_ui->txtPassword->text());
                        targetFile.write(crypt.cryptToPlainTextExt(data));
                        targetFile.waitForBytesWritten(3000);
                        targetFile.flush();
                        targetFile.waitForBytesWritten(3000);

                        // Alles Ok
                        targetFile.close();
                        crypted.close();
                    }
                } else {
                    Message::error(QObject::tr("Can't open crypted file"));
                    return;
                }
            }

            // Nun die Datei entpacken
            if (!Zip::extract(packFile, dirPath)) {
                Message::error(QObject::tr("Can't open zip file"));
                return;
            }

            // Nun ist alles entpackt, das Ziparchiv nun löschen
            QFile configZip (packFile);
            if (!configZip.remove()) {
                Message::error(configZip.errorString(), QObject::tr("Import Configuration"));
            }

            QString saveName;
            QString savePath;
            QString ovpnFilePath = m_ui->txtImportPath->text().right(m_ui->txtImportPath->text().size() - m_ui->txtImportPath->text().lastIndexOf("/") -1);

            saveName = ovpnFilePath.left(ovpnFilePath.size()-6);
            savePath = dirPath + QString("/") + ovpnFilePath.left(ovpnFilePath.size()-6) + QString(".ovpn");

            if (m_ui->rbSaveAsName->isChecked()) {
                // ovpn umbennen
                QFile ovpnFile (savePath);
                if (ovpnFile.exists()) {
                    // umbenennen
                    ovpnFile.rename(dirPath + QString("/") + configName + QString(".ovpn"));
                    saveName = configName;
                }
            }
            savePath = dirPath + QString("/") + saveName + QString(".ovpn");

            QFile ovpnFile (dirPath + QString("/") + configName + QString(".ovpn"));
            if (!ovpnFile.exists()) {
                Message::error(QObject::tr("Import failed! Removing empty directory."), QObject::tr("Import Configuration"));
                dirobj.rmdir(dirPath);
            } else {
                Preferences::instance()->addNewConfigToDatabase(saveName, savePath.replace("\\", "/"));
                Preferences::instance()->refreshConfigList();
                Preferences::instance()->setConnectionStatus();
                Message::information(QObject::tr("Import successfully ended!"), QObject::tr("Import Configuration"));
                Preferences::instance()->refreshDialog();
                Preferences::instance()->setIcon();
                this->close();
            }
        } else {
            Message::error(QObject::tr("No import file selected!"), QObject::tr("Import Configuration"));
        }
    }
}