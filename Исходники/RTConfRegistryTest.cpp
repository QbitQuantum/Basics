static void portable_setenv(const char* key, const char* value) {
#ifdef SK_BUILD_FOR_WIN32
    _putenv_s(key, value);
#else
    setenv(key, value, 1);
#endif
}