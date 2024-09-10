void setAutorunState(int autorun)
{
    QSettings *reg;
    if (autorun == autorunDisabled)
    {
        reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->remove("Byfly-Agent");
        delete reg;
        reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->remove("Byfly-Agent");
        delete reg;
    }
    else if (autorun == autorunForCurrentUser)
    {
        setAutorunState(autorunDisabled);
        reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->setValue("Byfly-Agent", qApp->applicationFilePath());
        delete reg;
    }
    else if (autorun == autorunForAllUsers)
    {
        setAutorunState(autorunDisabled);
        reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->setValue("Byfly-Agent", qApp->applicationFilePath());
        delete reg;
    }
}