    static unsigned long long str_to_int(const char* str) {
#ifdef _MSC_VER
        return _strtoui64(str, nullptr, 10);
#else
        return std::strtoull(str, nullptr, 10);
#endif
    }