/*
 * Convert long path to short path
 */
QString AbstractTool::pathToShort(const QString &longPath)
{
    QString shortPath;
    DWORD buffSize = GetShortPathNameW(reinterpret_cast<const wchar_t*>(longPath.utf16()), NULL, NULL);

    if(buffSize > 0)
    {
        wchar_t *buffer = new wchar_t[buffSize];
        DWORD result = GetShortPathNameW(reinterpret_cast<const wchar_t*>(longPath.utf16()), buffer, buffSize);

        if(result > 0 && result < buffSize)
        {
            shortPath = QString::fromUtf16(reinterpret_cast<const unsigned short*>(buffer));
        }

        delete[] buffer;
    }

    return (shortPath.isEmpty() ? longPath : shortPath);
}