/**************************************************************************
* ICPanel_IContextMenu_InvokeCommand()
*/
HRESULT WINAPI CControlPanelFolder::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
    WCHAR szPath[MAX_PATH];
    char szTarget[MAX_PATH];
    STRRET strret;
    WCHAR* pszPath;
    INT Length, cLength;
    CComPtr<IPersistFile>                ppf;
    CComPtr<IShellLinkA>                isl;
    HRESULT hResult;

    PIDLCPanelStruct *pcpanel = _ILGetCPanelPointer(apidl[0]);

    TRACE("(%p)->(invcom=%p verb=%p wnd=%p)\n", this, lpcmi, lpcmi->lpVerb, lpcmi->hwnd);

    if (lpcmi->lpVerb == MAKEINTRESOURCEA(IDS_OPEN)) //FIXME
    {
        LPITEMIDLIST lpIDList = ILCombine(pidlRoot, apidl[0]);

        if (!pcpanel)
        {
            /* UGLY HACK! */
            LPSHELLBROWSER lpSB = (LPSHELLBROWSER)SendMessageW(lpcmi->hwnd, CWM_GETISHELLBROWSER, 0, 0);
            HRESULT hr;

            if (lpSB == NULL)
                return E_FAIL;

            hr = lpSB->BrowseObject(lpIDList, 0);
            return hr;
        }

        /* Note: we pass the applet name to Control_RunDLL to distinguish between multiple applets in one .cpl file */
        ShellExecuteA(NULL, "cplopen", pcpanel->szName, pcpanel->szName + pcpanel->offsDispName, NULL, 0);
    }
    else if (lpcmi->lpVerb == MAKEINTRESOURCEA(IDS_CREATELINK)) //FIXME
    {
        if (!SHGetSpecialFolderPathW(NULL, szPath, CSIDL_DESKTOPDIRECTORY, FALSE))
            return E_FAIL;

        pszPath = PathAddBackslashW(szPath);
        if (!pszPath)
            return E_FAIL;

        if (GetDisplayNameOf(apidl[0], SHGDN_FORPARSING, &strret) != S_OK)
            return E_FAIL;

        Length =  MAX_PATH - (pszPath - szPath);
        cLength = strlen(strret.cStr);
        if (Length < cLength + 5)
        {
            FIXME("\n");
            return E_FAIL;
        }

        if (MultiByteToWideChar(CP_ACP, 0, strret.cStr, cLength + 1, pszPath, Length))
        {
            pszPath += cLength;
            Length -= cLength;
        }

        if (Length > 10)
        {
            wcscpy(pszPath, L" - ");
            cLength = LoadStringW(shell32_hInstance, IDS_LNK_FILE, &pszPath[3], Length - 4) + 3;
            if (cLength + 5 > Length)
                cLength = Length - 5;
            Length -= cLength;
            pszPath += cLength;
        }
        wcscpy(pszPath, L".lnk");

        pcpanel = _ILGetCPanelPointer(ILFindLastID(apidl[0]));
        if (pcpanel)
        {
            strncpy(szTarget, pcpanel->szName, MAX_PATH);
        }
        else
        {
            FIXME("Couldn't retrieve pointer to cpl structure\n");
            return E_FAIL;
        }
        hResult = CShellLink::_CreatorClass::CreateInstance(NULL, IID_PPV_ARG(IShellLinkA, &isl));
        if (SUCCEEDED(hResult))
        {
            isl->SetPath(szTarget);
            if (SUCCEEDED(isl->QueryInterface(IID_PPV_ARG(IPersistFile,&ppf))))
                ppf->Save(szPath, TRUE);
        }
        return NOERROR;
    }
    return S_OK;
}