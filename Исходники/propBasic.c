/*
* propBasicQuerySymlink
*
* Purpose:
*
* Set information values for SymbolicLink object type
*
* If ExtendedInfoAvailable is FALSE then it calls propSetDefaultInfo to set Basic page properties
*
*/
VOID propBasicQuerySymlink(
    _In_ PROP_OBJECT_INFO *Context,
    _In_ HWND hwndDlg,
    _In_ BOOL ExtendedInfoAvailable
)
{
    NTSTATUS    status;
    ULONG       bytesNeeded;
    HANDLE      hObject;
    LPWSTR      lpLinkTarget;
    TIME_FIELDS	SystemTime;
    WCHAR       szBuffer[MAX_PATH];

    OBJECT_BASIC_INFORMATION obi;

    SetDlgItemText(hwndDlg, ID_OBJECT_SYMLINK_TARGET, T_CannotQuery);
    SetDlgItemText(hwndDlg, ID_OBJECT_SYMLINK_CREATION, T_CannotQuery);

    if (Context == NULL) {
        return;
    }

    //
    // Open SymbolicLink object.
    //
    hObject = NULL;
    if (!propOpenCurrentObject(Context, &hObject, SYMBOLIC_LINK_QUERY)) {
        return;
    }

    //
    // Copy link target from main object list for performance reasons.
    // So we don't need to query same data again.
    //
    lpLinkTarget = Context->lpDescription;
    if (lpLinkTarget) {
        SetDlgItemText(hwndDlg, ID_OBJECT_SYMLINK_TARGET, lpLinkTarget);
    }

    //Query Link Creation Time
    RtlSecureZeroMemory(&obi, sizeof(OBJECT_BASIC_INFORMATION));

    status = NtQueryObject(hObject, ObjectBasicInformation, &obi,
        sizeof(OBJECT_BASIC_INFORMATION), &bytesNeeded);

    if (NT_SUCCESS(status)) {
        FileTimeToLocalFileTime((PFILETIME)&obi.CreationTime, (PFILETIME)&obi.CreationTime);
        RtlSecureZeroMemory(&SystemTime, sizeof(SystemTime));
        RtlTimeToTimeFields((PLARGE_INTEGER)&obi.CreationTime, (PTIME_FIELDS)&SystemTime);

        //Month starts from 0 index
        if (SystemTime.Month - 1 < 0) SystemTime.Month = 1;
        if (SystemTime.Month > 12) SystemTime.Month = 12;

        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        wsprintf(szBuffer, FORMATTED_TIME_DATE_VALUE,
            SystemTime.Hour,
            SystemTime.Minute,
            SystemTime.Second,
            SystemTime.Day,
            Months[SystemTime.Month - 1],
            SystemTime.Year);

        SetDlgItemText(hwndDlg, ID_OBJECT_SYMLINK_CREATION, szBuffer);
    }

    //
    // Query object basic and type info if needed.
    //
    if (ExtendedInfoAvailable == FALSE) {
        propSetDefaultInfo(Context, hwndDlg, hObject);
    }
    NtClose(hObject);
}