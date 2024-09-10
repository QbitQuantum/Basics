String openTemporaryFile(const String&, PlatformFileHandle& handle)
{
    handle = INVALID_HANDLE_VALUE;

    char tempPath[MAX_PATH];
    int tempPathLength = ::GetTempPathA(WTF_ARRAY_LENGTH(tempPath), tempPath);
    if (tempPathLength <= 0 || tempPathLength > WTF_ARRAY_LENGTH(tempPath))
        return String();

    HCRYPTPROV hCryptProv = 0;
    if (!CryptAcquireContext(&hCryptProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
        return String();

    char proposedPath[MAX_PATH];
    while (1) {
        char tempFile[] = "XXXXXXXX.tmp"; // Use 8.3 style name (more characters aren't helpful due to 8.3 short file names)
        const int randomPartLength = 8;
        if (!CryptGenRandom(hCryptProv, randomPartLength, reinterpret_cast<BYTE*>(tempFile)))
            break;

        // Limit to valid filesystem characters, also excluding others that could be problematic, like punctuation.
        // don't include both upper and lowercase since Windows file systems are typically not case sensitive.
        const char validChars[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < randomPartLength; ++i)
            tempFile[i] = validChars[tempFile[i] % (sizeof(validChars) - 1)];

        ASSERT(strlen(tempFile) == sizeof(tempFile) - 1);

        if (!PathCombineA(proposedPath, tempPath, tempFile))
            break;
 
        // use CREATE_NEW to avoid overwriting an existing file with the same name
        handle = CreateFileA(proposedPath, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
        if (!isHandleValid(handle) && GetLastError() == ERROR_ALREADY_EXISTS)
            continue;

        break;
    }

    CryptReleaseContext(hCryptProv, 0);

    if (!isHandleValid(handle))
        return String();

    return String::fromUTF8(proposedPath);
}