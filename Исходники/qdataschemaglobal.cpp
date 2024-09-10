QChar
toLower(QChar c)
{
#if QT_VERSION>=0x040000
// QT4 code
    return c.toLower();
#else
// QT3 code
    return c.lower();
#endif   
}