JNIEXPORT void JNICALL
Java_java_io_WinNTFileSystem_initIDs(JNIEnv *env, jclass cls)
{
    HMODULE handle;
    jclass fileClass;

    fileClass = (*env)->FindClass(env, "java/io/File");
    CHECK_NULL(fileClass);
    ids.path = (*env)->GetFieldID(env, fileClass, "path", "Ljava/lang/String;");
    CHECK_NULL(ids.path);

    // GetFinalPathNameByHandle requires Windows Vista or newer
    if (GetModuleHandleExW((GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT),
                           (LPCWSTR)&CreateFileW, &handle) != 0)
    {
        GetFinalPathNameByHandle_func = (GetFinalPathNameByHandleProc)
            GetProcAddress(handle, "GetFinalPathNameByHandleW");
    }
}