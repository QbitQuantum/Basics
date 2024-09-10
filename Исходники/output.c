INT_PTR CALLBACK NetworkOutputDlgProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    )
{
    PNETWORK_OUTPUT_CONTEXT context;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PNETWORK_OUTPUT_CONTEXT)lParam;
        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PNETWORK_OUTPUT_CONTEXT)GetProp(hwndDlg, L"Context");

        if (uMsg == WM_DESTROY)
            RemoveProp(hwndDlg, L"Context");
    }

    if (!context)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            WCHAR addressString[65];
            HANDLE pipeWriteHandle;

            PhCenterWindow(hwndDlg, GetParent(hwndDlg));
            context->WindowHandle = hwndDlg;

            if (context->Address.Type == PH_IPV4_NETWORK_TYPE)
                RtlIpv4AddressToString(&context->Address.InAddr, addressString);
            else
                RtlIpv6AddressToString(&context->Address.In6Addr, addressString);

            switch (context->Action)
            {
            case NETWORK_ACTION_PING:
            case NETWORK_ACTION_TRACEROUTE:
                if (context->Action == NETWORK_ACTION_PING)
                {
                    SetDlgItemText(hwndDlg, IDC_MESSAGE,
                        PhaFormatString(L"Pinging %s...", addressString)->Buffer);
                }
                else
                {
                    SetDlgItemText(hwndDlg, IDC_MESSAGE,
                        PhaFormatString(L"Tracing route to %s...", addressString)->Buffer);
                }

                // Doing this properly would be too complex, so we'll just
                // execute ping.exe/traceroute.exe and display its output.

                if (CreatePipe(&context->PipeReadHandle, &pipeWriteHandle, NULL, 0))
                {
                    STARTUPINFO startupInfo = { sizeof(startupInfo) };
                    PPH_STRING command;
                    OBJECT_HANDLE_FLAG_INFORMATION flagInfo;

                    startupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
                    startupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
                    startupInfo.hStdOutput = pipeWriteHandle;
                    startupInfo.hStdError = pipeWriteHandle;
                    startupInfo.wShowWindow = SW_HIDE;

                    if (context->Action == NETWORK_ACTION_PING)
                    {
                        command = PhaFormatString(
                            L"%s\\system32\\ping.exe %s",
                            USER_SHARED_DATA->NtSystemRoot,
                            addressString
                            );
                    }
                    else
                    {
                        command = PhaFormatString(
                            L"%s\\system32\\tracert.exe %s",
                            USER_SHARED_DATA->NtSystemRoot,
                            addressString
                            );
                    }

                    // Allow the write handle to be inherited.

                    flagInfo.Inherit = TRUE;
                    flagInfo.ProtectFromClose = FALSE;

                    NtSetInformationObject(
                        pipeWriteHandle,
                        ObjectHandleFlagInformation,
                        &flagInfo,
                        sizeof(OBJECT_HANDLE_FLAG_INFORMATION)
                        );

                    PhCreateProcessWin32Ex(
                        NULL,
                        command->Buffer,
                        NULL,
                        NULL,
                        &startupInfo,
                        PH_CREATE_PROCESS_INHERIT_HANDLES,
                        NULL,
                        NULL,
                        &context->ProcessHandle,
                        NULL
                        );

                    // Essential; when the process exits, the last instance of the pipe
                    // will be disconnected and our thread will exit.
                    NtClose(pipeWriteHandle);

                    // Create a thread which will wait for output and display it.
                    context->ThreadHandle = PhCreateThread(0, NetworkWorkerThreadStart, context);
                }

                break;
            }
        }
        break;
    case WM_DESTROY:
        {
            PhAcquireQueuedLockExclusive(&context->WindowHandleLock);
            context->WindowHandle = NULL;
            PhReleaseQueuedLockExclusive(&context->WindowHandleLock);

            if (context->ProcessHandle)
            {
                NtTerminateProcess(context->ProcessHandle, STATUS_SUCCESS);
                NtClose(context->ProcessHandle);
            }
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDCANCEL:
            case IDOK:
                EndDialog(hwndDlg, IDOK);
                break;
            }
        }
        break;
    case NTM_DONE:
        {
            SetDlgItemText(hwndDlg, IDC_MESSAGE, L"Finished.");
        }
        break;
    case NTM_RECEIVED:
        {
            OEM_STRING inputString;
            UNICODE_STRING convertedString;

            if (wParam != 0)
            {
                inputString.Buffer = (PCHAR)lParam;
                inputString.Length = (USHORT)wParam;

                if (NT_SUCCESS(RtlOemStringToUnicodeString(&convertedString, &inputString, TRUE)))
                {
                    PhAppendStringBuilderEx(&context->ReceivedString, convertedString.Buffer, convertedString.Length);
                    RtlFreeUnicodeString(&convertedString);

                    // Remove leading newlines.
                    if (
                        context->ReceivedString.String->Length >= 2 * 2 &&
                        context->ReceivedString.String->Buffer[0] == '\r' && context->ReceivedString.String->Buffer[1] == '\n'
                        )
                    {
                        PhRemoveStringBuilder(&context->ReceivedString, 0, 2);
                    }

                    SetDlgItemText(hwndDlg, IDC_TEXT, context->ReceivedString.String->Buffer);
                    SendMessage(
                        GetDlgItem(hwndDlg, IDC_TEXT),
                        EM_SETSEL,
                        context->ReceivedString.String->Length / 2 - 1,
                        context->ReceivedString.String->Length / 2 - 1
                        );
                    SendMessage(GetDlgItem(hwndDlg, IDC_TEXT), WM_VSCROLL, SB_BOTTOM, 0);
                }
            }
        }
        break;
    }

    return FALSE;
}