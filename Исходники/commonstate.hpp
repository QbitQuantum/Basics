    static std::string stringf(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        IGNORE_FORMAT_STRING_ON
        auto size = _vscprintf(format, args) + 1U;
        IGNORE_FORMAT_STRING_OFF
        std::unique_ptr<char[]> buf(new char[size] ); 

#ifndef _MSC_VER
        IGNORE_FORMAT_STRING_ON
        vsnprintf(buf.get(), size, format, args);
        IGNORE_FORMAT_STRING_OFF
#else
        vsnprintf_s(buf.get(), size, _TRUNCATE, format, args);
#endif

        va_end(args);            

        return std::string(buf.get());
    }