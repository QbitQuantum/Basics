    void log_vargs(const char* channel,
                   astra_log_severity_t logLevel,
                   const char* fileName,
                   int lineNo,
                   const char* func,
                   const char* format,
                   va_list args)
    {
#ifdef _WIN32
        int len = _vscprintf(format, args);
#else
        va_list argsCopy;
        va_copy(argsCopy, args);
        int len = vsnprintf(nullptr, 0, format, argsCopy);
        va_end(argsCopy);
#endif
        std::unique_ptr<char[]> buffer(new char[len + 1]);
        vsnprintf(buffer.get(), len + 1, format, args);

        dispatch_log(fileName, lineNo, func, channel, logLevel, buffer.get());
    }