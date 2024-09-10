HINSTANCE QSystemLibrary::load(const wchar_t *libraryName, bool onlySystemDirectory /* = true */)
{
    QStringList searchOrder;

#if !defined(QT_BOOTSTRAPPED)
    if (!onlySystemDirectory)
        searchOrder << QFileInfo(qAppFileName()).path();
#endif
    searchOrder << qSystemDirectory();

    if (!onlySystemDirectory) {
        const QString PATH = QString::fromWCharArray((const wchar_t *)_wgetenv(L"PATH"));
        searchOrder << PATH.split(QLatin1Char(';'), QString::SkipEmptyParts);
    }

    const QString fileName = QString::fromWCharArray(libraryName) + QLatin1String(".dll");
    // Start looking in the order specified
    for (int i = 0; i < searchOrder.count(); ++i) {
        QString fullPathAttempt = searchOrder.at(i);
        if (!fullPathAttempt.endsWith(QLatin1Char('\\')))
            fullPathAttempt.append(QLatin1Char('\\'));
        fullPathAttempt.append(fileName);
        HINSTANCE inst = ::LoadLibrary((const wchar_t *)fullPathAttempt.utf16());
        if (inst != 0)
            return inst;
    }

    return 0;
}