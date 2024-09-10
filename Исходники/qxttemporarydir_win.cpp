QString QxtTemporaryDirPrivate::create()
{
    QString res;
    wchar_t buffer[MAX_PATH];
    QFileInfo fileInfo(dirTemplate);
    UINT uUnique = GetTempFileNameW((wchar_t*)fileInfo.path().utf16(), (wchar_t*)fileInfo.baseName().utf16(), 0, buffer);
    if (uUnique != 0)
    {
        res = QString::fromUtf16((const ushort*)buffer);
        QFile::remove(res);
        QDir().mkpath(res);
    }
    return res;
}