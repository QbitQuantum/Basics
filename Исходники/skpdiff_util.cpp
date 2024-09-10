SkString get_absolute_path(const SkString& path) {
#if SK_BUILD_FOR_MAC || SK_BUILD_FOR_UNIX || SK_BUILD_FOR_ANDROID
    SkString fullPath(PATH_MAX + 1);
    if (realpath(path.c_str(), fullPath.writable_str()) == NULL) {
        fullPath.reset();
    }
    return fullPath;
#elif SK_BUILD_FOR_WIN32
    SkString fullPath(MAX_PATH);
    if (_fullpath(fullPath.writable_str(), path.c_str(), MAX_PATH) == NULL) {
        fullPath.reset();
    }
    return fullPath;
#else
    return SkString();
#endif
}