std::FILE *fopen(const char *path, const char *mode) {
#ifdef _WIN32
    try {
        return _wfsopen(u8string(path).to_wide(true).c_str(), u8string(mode).to_wide(true).c_str(), _SH_DENYNO);
    } catch(unicode_conversion_error) {
        errno = EINVAL;
        return nullptr;
    }
#else
    return std::fopen(path, mode);
#endif
}