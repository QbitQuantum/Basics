bool StFileNode::isFileExists(const StCString& thePath) {
#ifdef _WIN32
    StStringUtfWide aPath;
    aPath.fromUnicode(thePath);
    struct __stat64 aStatBuffer;
    return _wstat64(aPath.toCString(), &aStatBuffer) == 0;
#elif (defined(__APPLE__))
    struct stat aStatBuffer;
    return stat(thePath.toCString(), &aStatBuffer) == 0;
#else
    struct stat64 aStatBuffer;
    return stat64(thePath.toCString(), &aStatBuffer) == 0;
#endif
}