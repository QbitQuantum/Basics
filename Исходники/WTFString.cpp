String String::format(const char *format, ...)
{
#if PLATFORM(QT)
    // Use QString::vsprintf to avoid the locale dependent formatting of vsnprintf.
    // https://bugs.webkit.org/show_bug.cgi?id=18994
    va_list args;
    va_start(args, format);

    QString buffer;
    buffer.vsprintf(format, args);

    va_end(args);

    QByteArray ba = buffer.toUtf8();
    return StringImpl::create(ba.constData(), ba.length());

#elif OS(WINCE)
    va_list args;
    va_start(args, format);

    Vector<char, 256> buffer;

    int bufferSize = 256;
    buffer.resize(bufferSize);
    for (;;) {
        int written = vsnprintf(buffer.data(), bufferSize, format, args);
        va_end(args);

        if (written == 0)
            return String("");
        if (written > 0)
            return StringImpl::create(buffer.data(), written);
        
        bufferSize <<= 1;
        buffer.resize(bufferSize);
        va_start(args, format);
    }

#else
    va_list args;
    va_start(args, format);

    Vector<char, 256> buffer;

    // Do the format once to get the length.
#if COMPILER(MSVC)
    int result = _vscprintf(format, args);
#else
    char ch;
    int result = vsnprintf(&ch, 1, format, args);
    // We need to call va_end() and then va_start() again here, as the
    // contents of args is undefined after the call to vsnprintf
    // according to http://man.cx/snprintf(3)
    //
    // Not calling va_end/va_start here happens to work on lots of
    // systems, but fails e.g. on 64bit Linux.
    va_end(args);
    va_start(args, format);
#endif

    if (result == 0)
        return String("");
    if (result < 0)
        return String();
    unsigned len = result;
    buffer.grow(len + 1);
    
    // Now do the formatting again, guaranteed to fit.
    vsnprintf(buffer.data(), buffer.size(), format, args);

    va_end(args);
    
    return StringImpl::create(buffer.data(), len);
#endif
}