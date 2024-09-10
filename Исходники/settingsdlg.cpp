BOOL ChooseFolder(HWND hwnd)
{
    BOOL bRet = FALSE;
    BROWSEINFOW bi;
    ATL::CStringW szChooseFolderText;

    szChooseFolderText.LoadStringW(IDS_CHOOSE_FOLDER_TEXT);

    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = hwnd;
    bi.pidlRoot = NULL;
    bi.lpszTitle = szChooseFolderText.GetString();
    bi.ulFlags = BIF_USENEWUI | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | /* BIF_BROWSEFILEJUNCTIONS | */ BIF_VALIDATE;

    if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        ATL::CStringW szBuf;

        LPITEMIDLIST lpItemList = SHBrowseForFolderW(&bi);
        if (lpItemList && SHGetPathFromIDListW(lpItemList, szBuf.GetBuffer(MAX_PATH)))
        {
            szBuf.ReleaseBuffer();
            if (!szBuf.IsEmpty())
            {
                SetDlgItemTextW(hwnd, IDC_DOWNLOAD_DIR_EDIT, szBuf.GetString());
                bRet = TRUE;
            }
        }
        else
        {
            szBuf.ReleaseBuffer();
        }

        CoTaskMemFree(lpItemList);
        CoUninitialize();
    }

    return bRet;
}