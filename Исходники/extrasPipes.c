/*
* PipeQueryInfo
*
* Purpose:
*
* Query basic info about pipe.
*
*/
VOID PipeQueryInfo(
    PROP_OBJECT_INFO *Context,
    HWND hwndDlg
)
{
    LPWSTR                      lpType;
    HANDLE                      hPipe;
    NTSTATUS                    status;
    WCHAR                       szBuffer[MAX_PATH];
    IO_STATUS_BLOCK             iost;
    FILE_PIPE_LOCAL_INFORMATION fpli;

    //validate context
    if (Context == NULL) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        PipeDisplayError(hwndDlg);
        return;
    }
    if (
        (Context->lpObjectName == NULL) ||
        (Context->lpCurrentObjectPath == NULL)
        )
    {
        SetLastError(ERROR_OBJECT_NOT_FOUND);
        PipeDisplayError(hwndDlg);
        return;
    }

    SetDlgItemText(hwndDlg, ID_PIPE_FULLPATH, Context->lpCurrentObjectPath);

    //open pipe
    hPipe = NULL;
    if (!PipeOpenObjectMethod(Context, &hPipe, GENERIC_READ)) {
        //on error display last win32 error
        PipeDisplayError(hwndDlg);
        return;
    }

    RtlSecureZeroMemory(&fpli, sizeof(fpli));
    status = NtQueryInformationFile(hPipe, &iost, &fpli, sizeof(fpli), FilePipeLocalInformation);
    if (NT_SUCCESS(status)) {

        //Type
        lpType = TEXT("?");
        switch (fpli.NamedPipeType) {
        case FILE_PIPE_BYTE_STREAM_TYPE:
            lpType = TEXT("Byte stream");
            break;
        case FILE_PIPE_MESSAGE_TYPE:
            lpType = TEXT("Message");
            break;
        }
        SetDlgItemText(hwndDlg, ID_PIPE_TYPEMODE, lpType);

        //AccessMode
        lpType = TEXT("?");
        switch (fpli.NamedPipeConfiguration) {
        case FILE_PIPE_INBOUND:
            lpType = TEXT("Inbound");
            break;
        case FILE_PIPE_OUTBOUND:
            lpType = TEXT("Outbound");
            break;
        case FILE_PIPE_FULL_DUPLEX:
            lpType = TEXT("Duplex");
            break;
        }
        SetDlgItemText(hwndDlg, ID_PIPE_ACCESSMODE, lpType);

        //CurrentInstances
        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        ultostr(fpli.CurrentInstances, szBuffer);
        SetDlgItemText(hwndDlg, ID_PIPE_CURINSTANCES, szBuffer);

        //MaximumInstances
        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        if (fpli.MaximumInstances == MAXDWORD) {
            _strcpy(szBuffer, TEXT("Unlimited"));
        }
        else {
            ultostr(fpli.MaximumInstances, szBuffer);
        }
        SetDlgItemText(hwndDlg, ID_PIPE_MAXINSTANCES, szBuffer);

        //InboundQuota
        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        ultostr(fpli.InboundQuota, szBuffer);
        SetDlgItemText(hwndDlg, ID_PIPE_INBUFFER, szBuffer);

        //OutboundQuota
        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        ultostr(fpli.OutboundQuota, szBuffer);
        SetDlgItemText(hwndDlg, ID_PIPE_OUTBUFFER, szBuffer);

        //WriteQuotaAvailable
        RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
        ultostr(fpli.WriteQuotaAvailable, szBuffer);
        SetDlgItemText(hwndDlg, ID_PIPE_WRITEQUOTAAVAIL, szBuffer);
    }
    else {
        //show detail on query error
        SetLastError(RtlNtStatusToDosError(status));
        PipeDisplayError(hwndDlg);
    }
    NtClose(hPipe);
}