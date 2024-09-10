SAWYER_EXPORT boost::uint64_t
strtoull(const char *input, char **rest, int base) {
#ifdef _MSC_VER
    return _strtoui64(input, rest, base);
#else
    return ::strtoull(input, rest, base);
#endif
}