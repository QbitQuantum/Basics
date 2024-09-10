INT_PTR CALLBACK PhpSessionPropertiesDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            ULONG sessionId = (ULONG)lParam;
            WINSTATIONINFORMATION winStationInfo;
            BOOLEAN haveWinStationInfo;
            WINSTATIONCLIENT clientInfo;
            BOOLEAN haveClientInfo;
            ULONG returnLength;
            PWSTR stateString;

            SetProp(hwndDlg, L"SessionId", UlongToHandle(sessionId));
            PhCenterWindow(hwndDlg, GetParent(hwndDlg));

            // Query basic session information

            haveWinStationInfo = WinStationQueryInformationW(
                NULL,
                sessionId,
                WinStationInformation,
                &winStationInfo,
                sizeof(WINSTATIONINFORMATION),
                &returnLength
                );

            // Query client information

            haveClientInfo = WinStationQueryInformationW(
                NULL,
                sessionId,
                WinStationClient,
                &clientInfo,
                sizeof(WINSTATIONCLIENT),
                &returnLength
                );

            if (haveWinStationInfo)
            {
                SetDlgItemText(hwndDlg, IDC_USERNAME,
                    PhaFormatString(L"%s\\%s", winStationInfo.Domain, winStationInfo.UserName)->Buffer);
            }

            SetDlgItemInt(hwndDlg, IDC_SESSIONID, sessionId, FALSE);

            if (haveWinStationInfo)
            {
                if (PhFindStringSiKeyValuePairs(
                    PhpConnectStatePairs,
                    sizeof(PhpConnectStatePairs),
                    winStationInfo.ConnectState,
                    &stateString
                    ))
                {
                    SetDlgItemText(hwndDlg, IDC_STATE, stateString);
                }
            }

            if (haveWinStationInfo && winStationInfo.LogonTime.QuadPart != 0)
            {
                SYSTEMTIME systemTime;
                PPH_STRING time;

                PhLargeIntegerToLocalSystemTime(&systemTime, &winStationInfo.LogonTime);
                time = PhFormatDateTime(&systemTime);
                SetDlgItemText(hwndDlg, IDC_LOGONTIME, time->Buffer);
                PhDereferenceObject(time);
            }

            if (haveWinStationInfo && winStationInfo.ConnectTime.QuadPart != 0)
            {
                SYSTEMTIME systemTime;
                PPH_STRING time;

                PhLargeIntegerToLocalSystemTime(&systemTime, &winStationInfo.ConnectTime);
                time = PhFormatDateTime(&systemTime);
                SetDlgItemText(hwndDlg, IDC_CONNECTTIME, time->Buffer);
                PhDereferenceObject(time);
            }

            if (haveWinStationInfo && winStationInfo.DisconnectTime.QuadPart != 0)
            {
                SYSTEMTIME systemTime;
                PPH_STRING time;

                PhLargeIntegerToLocalSystemTime(&systemTime, &winStationInfo.DisconnectTime);
                time = PhFormatDateTime(&systemTime);
                SetDlgItemText(hwndDlg, IDC_DISCONNECTTIME, time->Buffer);
                PhDereferenceObject(time);
            }

            if (haveWinStationInfo && winStationInfo.LastInputTime.QuadPart != 0)
            {
                SYSTEMTIME systemTime;
                PPH_STRING time;

                PhLargeIntegerToLocalSystemTime(&systemTime, &winStationInfo.LastInputTime);
                time = PhFormatDateTime(&systemTime);
                SetDlgItemText(hwndDlg, IDC_LASTINPUTTIME, time->Buffer);
                PhDereferenceObject(time);
            }

            if (haveClientInfo && clientInfo.ClientName[0] != 0)
            {
                WCHAR addressString[65];

                SetDlgItemText(hwndDlg, IDC_CLIENTNAME, clientInfo.ClientName);

                if (clientInfo.ClientAddressFamily == AF_INET6)
                {
                    struct in6_addr address;
                    ULONG i;
                    PUSHORT in;
                    PUSHORT out;

                    // IPv6 is special - the client address data is a reversed version of
                    // the real address.

                    in = (PUSHORT)clientInfo.ClientAddress;
                    out = (PUSHORT)address.u.Word;

                    for (i = 8; i != 0; i--)
                    {
                        *out = _byteswap_ushort(*in);
                        in++;
                        out++;
                    }

                    RtlIpv6AddressToString(&address, addressString);
                }
                else
                {
                    wcscpy_s(addressString, 65, clientInfo.ClientAddress);
                }

                SetDlgItemText(hwndDlg, IDC_CLIENTADDRESS, addressString);

                SetDlgItemText(hwndDlg, IDC_CLIENTDISPLAY,
                    PhaFormatString(L"%ux%u@%u", clientInfo.HRes,
                    clientInfo.VRes, clientInfo.ColorDepth)->Buffer
                    );
            }

            SendMessage(hwndDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hwndDlg, IDOK), TRUE);
        }
        break;
    case WM_DESTROY:
        {
            RemoveProp(hwndDlg, L"SessionId");
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
    }

    return FALSE;
}