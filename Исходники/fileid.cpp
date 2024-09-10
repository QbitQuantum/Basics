FileId::Md5Hash FileId::hash(String path)
{
    // Ensure we've a normalized path.
    if(QDir::isRelativePath(path))
    {
        path = App_BasePath() / path;
    }

#if defined(WIN32) || defined(MACOSX)
    // This is a case insensitive operation.
    path = path.toUpper();
#endif
    return QCryptographicHash::hash(path.toUtf8(), QCryptographicHash::Md5);
}