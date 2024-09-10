std::string errnoWithDescription(int errNumber) {
#if defined(_WIN32)
    if (errNumber == -1)
        errNumber = GetLastError();
#else
    if (errNumber < 0)
        errNumber = errno;
#endif

    char buf[kBuflen];
    char* msg{nullptr};

#if defined(__GNUC__) && defined(_GNU_SOURCE) && !(__ANDROID_API__ <= 22) && !defined(EMSCRIPTEN)
    msg = strerror_r(errNumber, buf, kBuflen);
#elif defined(_WIN32)

    LPWSTR errorText = nullptr;
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr,
                   errNumber,
                   0,
                   reinterpret_cast<LPWSTR>(&errorText),  // output
                   0,                                     // minimum size for output buffer
                   nullptr);

    if (errorText) {
        ON_BLOCK_EXIT([&errorText] { LocalFree(errorText); });
        std::string utf8ErrorText = toUtf8String(errorText);
        auto size = utf8ErrorText.find_first_of("\r\n");
        if (size == std::string::npos) {  // not found
            size = utf8ErrorText.length();
        }

        if (size >= kBuflen) {
            size = kBuflen - 1;
        }

        memcpy(buf, utf8ErrorText.c_str(), size);
        buf[size] = '\0';
        msg = buf;
    } else if (strerror_s(buf, kBuflen, errNumber) != 0) {
        msg = buf;
    }
#else /* XSI strerror_r */
    if (strerror_r(errNumber, buf, kBuflen) == 0) {
        msg = buf;
    }
#endif

    if (!msg) {
        return str::stream() << kUnknownMsg << errNumber;
    }

    return {msg};
}