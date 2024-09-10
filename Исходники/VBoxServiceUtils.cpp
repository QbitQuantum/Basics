/**
 * Helper for VBoxServiceGetFileVersion and attempts to read and parse
 * FileVersion.
 *
 * @returns Success indicator.
 */
static bool VBoxServiceGetFileVersionOwn(LPSTR pVerData,
                                         PDWORD pdwMajor,
                                         PDWORD pdwMinor,
                                         PDWORD pdwBuildNumber,
                                         PDWORD pdwRevisionNumber)
{
    UINT    cchStrValue = 0;
    LPTSTR  pStrValue   = NULL;
    if (!VerQueryValueA(pVerData, "\\StringFileInfo\\040904b0\\FileVersion", (LPVOID *)&pStrValue, &cchStrValue))
        return false;

    /** @todo r=bird: get rid of this. Avoid sscanf like the plague! */
    if (sscanf(pStrValue, "%ld.%ld.%ld.%ld", pdwMajor, pdwMinor, pdwBuildNumber, pdwRevisionNumber) != 4)
        return false;

    return true;
}