/*
 * Returns the security descriptor for a file.
 */
static SECURITY_DESCRIPTOR* getFileSecurityDescriptor(JNIEnv* env, const char* path) {
    SECURITY_DESCRIPTOR* sd;
    DWORD len = 0;
    SECURITY_INFORMATION info =
        OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;

    GetFileSecurityA(path, info , 0, 0, &len);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        JNU_ThrowIOExceptionWithLastError(env, "GetFileSecurity failed");
        return NULL;
    }
    sd = (SECURITY_DESCRIPTOR *)malloc(len);
    if (sd == NULL) {
        JNU_ThrowOutOfMemoryError(env, 0);
    } else {
        if (!(*GetFileSecurityA)(path, info, sd, len, &len)) {
            JNU_ThrowIOExceptionWithLastError(env, "GetFileSecurity failed");
            free(sd);
            return NULL;
        }
    }
    return sd;
}