/*
 * Class:     com_kenai_jffi_Foreign
 * Method:    dlopen
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL
Java_com_kenai_jffi_Foreign_dlopen(JNIEnv* env, jobject self, jstring jPath, jint jFlags)
{
#ifdef _WIN32
    if (jPath == NULL) {
        return p2j(GetModuleHandle(NULL));
    } else {
        wchar_t path[PATH_MAX];
        DWORD dwFlags;
        getWideString(env, path, jPath, sizeof(path) / sizeof(path[0]));
        dwFlags = PathIsRelativeW(path) ? 0 : LOAD_WITH_ALTERED_SEARCH_PATH;
        return p2j(LoadLibraryExW(path, NULL, dwFlags));
    }
#else
    char path_[PATH_MAX];
    const char* path = NULL; // Handle dlopen(NULL, flags);
    void* handle = NULL;
    int flags = 0;
#define F(x) (jFlags & com_kenai_jffi_Foreign_RTLD_##x) != 0 ? RTLD_##x : 0;
    flags |= F(LAZY);
    flags |= F(GLOBAL);
    flags |= F(LOCAL);
    flags |= F(NOW);
#undef F

#ifdef _AIX
    flags |= RTLD_MEMBER; //  Needed for AIX
#endif
    
    if (jPath != NULL) {
        path = path_;
        getMultibyteString(env, path_, jPath, sizeof(path_));
    }

    handle = dl_open(path, flags);
    if (handle == NULL) {
        char errbuf[1024] = { 0 };
        dl_error(errbuf, sizeof(errbuf) - 1);
        throwException(env, UnsatisfiedLink, "%s", errbuf);
    }
    
    return p2j(handle);
#endif
}