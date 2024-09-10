 string getString()
 {
    const int timeBufferLen = 1024;
    char timestr[timeBufferLen];
    char buffer[timeBufferLen];
    struct tm t;
    _localtime64_s(&t, &time_.time);
    std::strftime(timestr, timeBufferLen, "%Y.%m.%d %H:%M:%S", &t);
    _snprintf_s(buffer, timeBufferLen, "%s.%d", timestr, time_.millitm);
    return buffer;
 }