BOOL
GetCurrentHwProfileA (
    OUT LPHW_PROFILE_INFOA  lpHwProfileInfo
)

/*++

Routine Description:


Arguments:

    lpHwProfileInfo  Points to a HW_PROFILE_INFO structure that will receive
                     the information for the current hardware profile.

Return Value:

    If the function succeeds, the return value is TRUE.  If the function
    fails, the return value is FALSE.  To get extended error information,
    call GetLastError.

--*/

{
    BOOL              Status = TRUE;
    HW_PROFILE_INFOW  HwProfileInfoW;
    LPSTR             pAnsiString;


    try {
        //
        // validate parameter
        //
        if (lpHwProfileInfo == NULL) {
            SetLastError(ERROR_INVALID_PARAMETER);
            Status = FALSE;
            goto Clean0;
        }

        //
        // call the Unicode version
        //
        if (!GetCurrentHwProfileW(&HwProfileInfoW)) {
            Status = FALSE;
            goto Clean0;
        }

        //
        // on successful return, convert unicode form of struct
        // to ANSI and copy struct members to callers struct
        //
        lpHwProfileInfo->dwDockInfo = HwProfileInfoW.dwDockInfo;

        pAnsiString = UnicodeToMultiByte(
                          HwProfileInfoW.szHwProfileGuid, CP_ACP);
        lstrcpyA(lpHwProfileInfo->szHwProfileGuid, pAnsiString);
        LocalFree(pAnsiString);

        pAnsiString = UnicodeToMultiByte(
                          HwProfileInfoW.szHwProfileName, CP_ACP);
        lstrcpyA(lpHwProfileInfo->szHwProfileName, pAnsiString);
        LocalFree(pAnsiString);


Clean0:
        ;

    }
    except(EXCEPTION_EXECUTE_HANDLER) {
        SetLastError(ERROR_INTERNAL_ERROR);
        Status = FALSE;
    }

    return Status;

} // GetCurrentHwProfileA