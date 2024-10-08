/*
 * Class:     sun_awt_windows_WDesktopPeer
 * Method:    ShellExecute
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_sun_awt_windows_WDesktopPeer_ShellExecute
  (JNIEnv *env, jclass cls, jstring uri_j, jstring verb_j)
{
    const WCHAR* uri_c = env->GetStringChars(uri_j, JNI_FALSE);
    const WCHAR* verb_c = env->GetStringChars(verb_j, JNI_FALSE);

    // 6457572: ShellExecute possibly changes FPU control word - saving it here
    unsigned oldcontrol87 = _control87(0, 0);
    HINSTANCE retval = ShellExecuteW(NULL, verb_c, uri_c, NULL, NULL, SW_SHOWNORMAL);
    _control87(oldcontrol87, 0xffffffff);

    env->ReleaseStringChars(uri_j, uri_c);
    env->ReleaseStringChars(verb_j, verb_c);

    if ((int)retval <= 32) {
        // ShellExecute failed.
        LPVOID buffer;
        int len = FormatMessageW(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM  |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    GetLastError(),
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                    (LPWSTR) &buffer,
                    0,
                    NULL );

        jstring errmsg = env->NewString((LPCWSTR)buffer, len);
        LocalFree(buffer);
        return errmsg;
    }

    return NULL;
}