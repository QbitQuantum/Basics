void printStringToConsole(const char* format, const QString& str){
    QByteArray ba = str.toLocal8Bit();
    char* buf = ba.data();
#ifdef Q_OS_WIN32
    // a bit of magic to workaround Windows console encoding issues
    CharToOemA(buf,buf);
#endif
    printf(format, buf);
}