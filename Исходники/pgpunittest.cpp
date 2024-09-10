// qt did not introduce qputenv until 4.4, so we'll keep a copy here for 4.2
//   compat
bool my_qputenv(const char *varName, const QByteArray& value)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    return _putenv_s(varName, value.constData()) == 0;
#else
    QByteArray buffer(varName);
    buffer += "=";
    buffer += value;
    return putenv(qstrdup(buffer.constData())) == 0;
#endif
}