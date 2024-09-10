int qt_wince__access( const char *path, int pmode )
{
    return _waccess(reinterpret_cast<const wchar_t *> (QString::fromLatin1(path).utf16()),pmode);
}