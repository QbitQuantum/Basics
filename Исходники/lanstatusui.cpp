VOID
UpdateLanStatus(HWND hwndDlg,  LANSTATUSUI_CONTEXT * pContext)
{
    MIB_IFROW IfEntry;
    HICON hIcon, hOldIcon = NULL;
    NOTIFYICONDATAW nid;
    NETCON_PROPERTIES * pProperties = NULL;

    ZeroMemory(&IfEntry, sizeof(IfEntry));
    IfEntry.dwIndex = pContext->dwAdapterIndex;
    if (GetIfEntry(&IfEntry) != NO_ERROR)
    {
        return;
    }

    hIcon = NULL;
    if (IfEntry.dwOperStatus == MIB_IF_OPER_STATUS_CONNECTED || IfEntry.dwOperStatus == MIB_IF_OPER_STATUS_OPERATIONAL)
    {
        if (pContext->dwInOctets == IfEntry.dwInOctets && pContext->dwOutOctets == IfEntry.dwOutOctets && pContext->Status  != 0)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_IDLE), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 0;
        }
        else if (pContext->dwInOctets != IfEntry.dwInOctets && pContext->dwOutOctets != IfEntry.dwOutOctets && pContext->Status  != 1)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_TRANSREC), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 1;
        }
        else if (pContext->dwInOctets != IfEntry.dwInOctets && pContext->Status  != 2)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_REC), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 2; 
        }
        else if (pContext->dwOutOctets != IfEntry.dwOutOctets && pContext->Status  != 3)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_TRANS), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 3;
        }
    }
    else if (IfEntry.dwOperStatus == MIB_IF_OPER_STATUS_UNREACHABLE || IfEntry.dwOperStatus == MIB_IF_OPER_STATUS_DISCONNECTED)
    {
        if (pContext->Status != 4)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_OFF), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 4;
        }
    }
    else if (IfEntry.dwOperStatus == MIB_IF_OPER_STATUS_NON_OPERATIONAL)
    {
        if (pContext->Status != 5)
        {
            hIcon = (HICON)LoadImage(netshell_hInstance, MAKEINTRESOURCE(IDI_NET_OFF), IMAGE_ICON, 32, 32, LR_SHARED);
            pContext->Status = 5;
        }
    }

    if (hwndDlg && hIcon)
    {
        hOldIcon = (HICON)SendDlgItemMessageW(hwndDlg, IDC_NETSTAT, STM_SETICON, (WPARAM)hIcon, 0);
        if (hOldIcon)
            DestroyIcon(hOldIcon);
    }

    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uID = pContext->uID;
    nid.hWnd = pContext->hwndStatusDlg;
    nid.uVersion = 3;

    if (pContext->pNet->GetProperties(&pProperties) == S_OK)
    {
        if (pProperties->dwCharacter & NCCF_SHOW_ICON)
        {
            if (hwndDlg)
                nid.hIcon = (HICON)CopyImage(hIcon, IMAGE_ICON, 16, 16, LR_COPYFROMRESOURCE);
            else
                nid.hIcon = hIcon;

            if (nid.hIcon)
                nid.uFlags |= NIF_ICON;

            nid.uFlags |= NIF_STATE;
            nid.dwState = 0;
            nid.dwStateMask = NIS_HIDDEN;

            if (pProperties->pszwName)
            {
                if (wcslen(pProperties->pszwName) * sizeof(WCHAR) < sizeof(nid.szTip))
                {
                    nid.uFlags |= NIF_TIP;
                    wcscpy(nid.szTip, pProperties->pszwName);
                }
                else
                {
                    CopyMemory(nid.szTip, pProperties->pszwName, sizeof(nid.szTip) - sizeof(WCHAR));
                    nid.szTip[(sizeof(nid.szTip)/sizeof(WCHAR))-1] = L'\0';
                    nid.uFlags |= NIF_TIP;
                }
            }
        }
        else
        {
            nid.uFlags |= NIF_STATE;
            nid.dwState = NIS_HIDDEN;
            nid.dwStateMask = NIS_HIDDEN;

        }
        NcFreeNetconProperties(pProperties);
    }

    Shell_NotifyIconW(NIM_MODIFY, &nid);

    if (nid.uFlags & NIF_ICON)
        DestroyIcon(nid.hIcon);

    pContext->dwInOctets = IfEntry.dwInOctets;
    pContext->dwOutOctets = IfEntry.dwOutOctets;

    if (hwndDlg)
        UpdateLanStatusUiDlg(hwndDlg, &IfEntry, pContext);
}