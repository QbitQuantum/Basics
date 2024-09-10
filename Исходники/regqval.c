LONG
REGAPI
VMMRegQueryValueEx(
    HKEY hKey,
    LPCSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    )
{

    int ErrorCode;
    LPKEY_RECORD lpKeyRecord;
    LPVALUE_RECORD lpValueRecord;

    if (IsBadOptionalStringPtr(lpValueName, (UINT) -1))
        return ERROR_INVALID_PARAMETER;

    if (IsBadHugeOptionalWritePtr(lpType, sizeof(DWORD)))
        return ERROR_INVALID_PARAMETER;

    if (IsNullPtr(lpcbData)) {
        if (!IsNullPtr(lpData))
            return ERROR_INVALID_PARAMETER;
    }

    else {
	//  Win95 compatibility: don't validate lpData is of size *lpcbData.
	//  Instead of validating the entire buffer, we'll validate just the
	//  required buffer length in RgCopyFromValueRecord.
	if (IsBadHugeWritePtr(lpcbData, sizeof(DWORD)))
	    return ERROR_INVALID_PARAMETER;
    }

    if (!RgLockRegistry())
        return ERROR_LOCK_FAILED;

    if ((ErrorCode = RgValidateAndConvertKeyHandle(&hKey)) == ERROR_SUCCESS) {

        if ((ErrorCode = RgLookupValueByName(hKey, lpValueName, &lpKeyRecord,
            &lpValueRecord)) == ERROR_SUCCESS) {

            ErrorCode = RgCopyFromValueRecord(hKey, lpValueRecord, NULL, NULL,
                lpType, lpData, lpcbData);
            RgUnlockDatablock(hKey-> lpFileInfo, hKey-> BlockIndex, FALSE);

        }

        else if (ErrorCode == ERROR_CANTREAD16_FILENOTFOUND32) {

            //
            //  Very stupid Windows 95 compatibility problem.  If the "value
            //  record" didn't exist in Windows 3.1, then it acted like it was
            //  really a null byte REG_SZ string.  This should have only been
            //  done in RegQueryValue, but we're stuck with it now...
            //

            if (IsNullPtr(lpValueName) || *lpValueName == '\0') {

                if (!IsNullPtr(lpType))
                    *lpType = REG_SZ;

                if (!IsNullPtr(lpData) && *lpcbData > 0)
                    *lpData = 0;

                if (!IsNullPtr(lpcbData))
                    *lpcbData = sizeof(char);

                ErrorCode = ERROR_SUCCESS;

            }

        }

    }

    RgUnlockRegistry();

    return ErrorCode;

    UNREFERENCED_PARAMETER(lpReserved);

}