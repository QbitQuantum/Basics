/**
 * The function deletes the directory named dirName from the persistent storage.
 */
int pcsl_file_rmdir(const pcsl_string * dirName)
{
    int res;
    const jchar * pszOsFilename = pcsl_string_get_utf16_data(dirName);

    if (NULL == pszOsFilename) {
        return -1;
    }

    res = _wrmdir(pszOsFilename);
    pcsl_string_release_utf16_data(pszOsFilename, dirName);

    return (0 == res) ? 0 : -1;
}