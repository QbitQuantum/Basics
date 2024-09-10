bool tCOMUtil::DelRegKey(const char *key,
                         const char *subkey)
{
    const int bufsize = 10000;
    char Key[bufsize];
    strncpy(Key, key, bufsize - 1);

    if (NULL != subkey)
    {
        strcat(Key, "\\");
        strcat(Key, subkey);
    }

    LONG ec = SHDeleteKeyA(HKEY_CLASSES_ROOT, Key);
    if (ERROR_SUCCESS == ec)
    {
        return true;
    }

    return false;
}