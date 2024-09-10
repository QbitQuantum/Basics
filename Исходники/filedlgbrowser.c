static void COMDLG32_UpdateCurrentDir(const FileOpenDlgInfos *fodInfos)
{
    LPSHELLFOLDER psfDesktop;
    STRRET strret;
    HRESULT res;

    res = SHGetDesktopFolder(&psfDesktop);
    if (FAILED(res))
        return;
    
    res = IShellFolder_GetDisplayNameOf(psfDesktop, fodInfos->ShellInfos.pidlAbsCurrent,
                                        SHGDN_FORPARSING, &strret);
    if (SUCCEEDED(res)) {
        WCHAR wszCurrentDir[MAX_PATH];
        
        res = StrRetToBufW(&strret, fodInfos->ShellInfos.pidlAbsCurrent, wszCurrentDir, MAX_PATH);
        if (SUCCEEDED(res))
            SetCurrentDirectoryW(wszCurrentDir);
    }
    
    IShellFolder_Release(psfDesktop);
}