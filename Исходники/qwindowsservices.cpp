// Retrieve the commandline for the default mail client. It contains a
// placeholder %1 for the URL. The default key used below is the
// command line for the mailto: shell command.
static inline QString mailCommand()
{
    enum { BufferSize = sizeof(wchar_t) * MAX_PATH };

    const wchar_t mailUserKey[] = L"Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\mailto\\UserChoice";

    wchar_t command[MAX_PATH] = {0};
    // Check if user has set preference, otherwise use default.
    HKEY handle;
    QString keyName;
    if (!RegOpenKeyEx(HKEY_CURRENT_USER, mailUserKey, 0, KEY_READ, &handle)) {
        DWORD bufferSize = BufferSize;
        if (!RegQueryValueEx(handle, L"Progid", 0, 0, reinterpret_cast<unsigned char*>(command), &bufferSize))
            keyName = QString::fromWCharArray(command);
        RegCloseKey(handle);
    }
    if (keyName.isEmpty())
        keyName = QStringLiteral("mailto");
    keyName += QStringLiteral("\\Shell\\Open\\Command");
    if (debug)
        qDebug() << __FUNCTION__ << "keyName=" << keyName;
    command[0] = 0;
    if (!RegOpenKeyExW(HKEY_CLASSES_ROOT, (const wchar_t*)keyName.utf16(), 0, KEY_READ, &handle)) {
        DWORD bufferSize = BufferSize;
        RegQueryValueEx(handle, L"", 0, 0, reinterpret_cast<unsigned char*>(command), &bufferSize);
        RegCloseKey(handle);
    }
    if (!command[0])
        return QString();
#ifndef Q_OS_WINCE
    wchar_t expandedCommand[MAX_PATH] = {0};
    return ExpandEnvironmentStrings(command, expandedCommand, MAX_PATH) ?
           QString::fromWCharArray(expandedCommand) : QString::fromWCharArray(command);
#else
    return QString();
#endif
}