JNIEXPORT jint SIGAR_JNI(win32_Pdh_pdhLookupPerfIndex)
(JNIEnv *env, jclass cur, jstring jname)
{
    DWORD index;
    LPCTSTR name =
        JENV->GetStringChars(env, jname, NULL);
    PDH_STATUS status =
        PdhLookupPerfIndexByNameW(NULL, name, &index);

    JENV->ReleaseStringChars(env, jname, name);

    if (status == ERROR_SUCCESS) {
        return index;
    }
    else {
        win32_throw_exception(env, get_error_message(status));
        return -1;
    }
}