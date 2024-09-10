// RunAtStartupEnabled
void MakeRT::RunAtStartupEnabled(bool startup)
{
    _settings->setValue(RUNATSTARTUP, startup);

#ifdef Q_OS_WIN
    HKEY key;
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &key);
    if (startup)
    {
        QString appFileName = qApp->applicationFilePath();
        if (RegSetValueExA(key, "MakeRT", 0, REG_SZ, (BYTE*)appFileName.toStdString().c_str(), appFileName.length()) != ERROR_SUCCESS)
        {
            QMessageBox::critical(this, tr("Failed!"), tr("Cannot set autostart in registry."));
            RunAtStartupEnabled(false);
        }
    }
    else
    {
        RegDeleteValueA(key, "MakeRT");
    }
    RegCloseKey(key);
#elif defined Q_OS_LINUX
    QString dir = QDir::homePath() + "/.config/autostart/";
    QString fileName = "MakeRT.desktop";
    QString data;
    if (startup)
    {
        QDir tmp(dir);
        if (!tmp.exists())
            tmp.mkpath(dir);
        QFile file(dir + fileName);
        if (!file.open(QFile::WriteOnly))
        {
            QMessageBox::critical(this, tr("Failed!"), tr("Cannot create autostart file!"));
            RunAtStartupEnabled(false);
            return;
        }

        data = "[Desktop Entry]\n";
        data += "Type=Application\n";
        data += "Name=MakeRT\n";
        data += "Exec=" + qApp->applicationFilePath() + "\n";
        file.write(data.toStdString().c_str());
        file.close();
    }
    else
        QFile::remove(dir + fileName);
#endif // Q_OS_WIN
}