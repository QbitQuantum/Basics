JNIEXPORT jlongArray JNICALL Java_org_jdesktop_jdic_fileutil_Win32NativeFileUtil_getTotalSpace
  (JNIEnv *env, jobject obj, jstring fullPath) {
    wchar_t* pFullPath = (wchar_t*) (*env)->GetStringChars(env, fullPath, NULL);
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;
    jlongArray retorno = (*env)->NewLongArray(env, 2);
    jlong buf[2];
    wchar_t* pTerminator = L"\0";

    pFullPath = (wchar_t*) realloc(pFullPath, sizeof(wchar_t) * (wcslen(pFullPath) + 1));
    wcsncat(pFullPath, pTerminator, 1);
    GetDiskFreeSpaceExW(pFullPath, &freeBytesAvailable, &totalNumberOfBytes, 
                             &totalNumberOfFreeBytes);
    buf[0] = (jlong) totalNumberOfBytes.LowPart;
    buf[1] = (jlong) totalNumberOfBytes.HighPart;
    (*env)->SetLongArrayRegion(env, retorno, 0, 2, buf);
    (*env)->ReleaseStringChars(env, fullPath, pFullPath);
    
    return retorno;
}