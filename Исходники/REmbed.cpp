int setenv(QString name, QString value, bool overwrite)
{
    int errcode = 0;
    if(!overwrite) {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name.toLatin1().constData());
        if(errcode || envsize) return errcode;
    }

    // make the update
    return _putenv_s(name.toLatin1().constData(), value.toLatin1().constData());
}