bool QLibraryPrivate::load_sys()
{
#ifndef Q_OS_WINRT
    //avoid 'Bad Image' message box
    UINT oldmode = SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOOPENFILEERRORBOX);
#endif
    // We make the following attempts at locating the library:
    //
    // WinCE
    // if (absolute)
    //     fileName
    //     fileName + ".dll"
    // else
    //     fileName + ".dll"
    //     fileName
    //     QFileInfo(fileName).absoluteFilePath()
    //
    // Windows
    // if (absolute)
    //     fileName
    //     fileName + ".dll"
    // else
    //     fileName + ".dll"
    //     fileName
    //
    // NB If it's a plugin we do not ever try the ".dll" extension
    QStringList attempts;

    if (pluginState != IsAPlugin)
        attempts.append(fileName + QLatin1String(".dll"));

    // If the fileName is an absolute path we try that first, otherwise we
    // use the system-specific suffix first
    QFileSystemEntry fsEntry(fileName);
    if (fsEntry.isAbsolute()) {
        attempts.prepend(fileName);
    } else {
        attempts.append(fileName);
#if defined(Q_OS_WINCE)
        attempts.append(QFileInfo(fileName).absoluteFilePath());
#endif
    }
#ifdef Q_OS_WINRT
    if (fileName.startsWith(QLatin1Char('/')))
        attempts.prepend(QDir::rootPath() + fileName);
#endif

    Q_FOREACH (const QString &attempt, attempts) {
#ifndef Q_OS_WINRT
        pHnd = LoadLibrary((wchar_t*)QDir::toNativeSeparators(attempt).utf16());
#else // Q_OS_WINRT
        QString path = QDir::toNativeSeparators(QDir::current().relativeFilePath(attempt));
        pHnd = LoadPackagedLibrary((LPCWSTR)path.utf16(), 0);
        if (pHnd)
            qualifiedFileName = attempt;
#endif // !Q_OS_WINRT

        // If we have a handle or the last error is something other than "unable
        // to find the module", then bail out
        if (pHnd || ::GetLastError() != ERROR_MOD_NOT_FOUND)
            break;
    }