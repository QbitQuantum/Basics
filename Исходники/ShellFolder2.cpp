/*
 * Class:     sun_awt_shell_Win32ShellFolder2
 * Method:    getEnumObjects
 * Signature: (JZ)J
 */
JNIEXPORT jlong JNICALL Java_sun_awt_shell_Win32ShellFolder2_getEnumObjects
    (JNIEnv* env, jobject folder, jlong pIShellFolder,
     jboolean isDesktop, jboolean includeHiddenFiles)
{
    IShellFolder* pFolder = (IShellFolder*)pIShellFolder;
    if (pFolder == NULL) {
        return 0;
    }
    DWORD dwFlags = SHCONTF_FOLDERS | SHCONTF_NONFOLDERS;
    if (includeHiddenFiles) {
        dwFlags |= SHCONTF_INCLUDEHIDDEN;
    }
        /*
    if (!isDesktop) {
        dwFlags = dwFlags | SHCONTF_NONFOLDERS;
    }
        */
    IEnumIDList* pEnum;
    if (pFolder->EnumObjects(NULL, dwFlags, &pEnum) != S_OK) {
        return 0;
    }
    return (jlong)pEnum;
}