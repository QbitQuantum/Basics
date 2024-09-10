/// This function is copied from QtCoreLib (>5.1)
/// and is not available in qt4
bool TIGLViewerWindow::deleteEnvVar(const char * varName)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    return _putenv_s(varName, "");
#elif (defined(_POSIX_VERSION) && (_POSIX_VERSION-0) >= 200112L) || defined(Q_OS_BSD4)
    // POSIX.1-2001 and BSD have unsetenv
    return unsetenv(varName) == 0;
#elif defined(Q_CC_MINGW)
    // On mingw, putenv("var=") removes "var" from the environment
    QByteArray buffer(varName);
    buffer += '=';
    return putenv(buffer.constData()) == 0;
#else
    // Fallback to putenv("var=") which will insert an empty var into the
    // environment and leak it
    QByteArray buffer(varName);
    buffer += '=';
    char *envVar = qstrdup(buffer.constData());
    return putenv(envVar) == 0;
#endif
}