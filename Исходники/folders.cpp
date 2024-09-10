BOOL
GetIconOverlay(LPCITEMIDLIST pidl, WCHAR * wTemp, int* pIndex)
{
    DWORD Index;
    HRESULT hResult;
    int Priority;
    int HighestPriority;
    ULONG IconIndex;
    ULONG Flags;
    WCHAR szPath[MAX_PATH];

    if(!SHGetPathFromIDListW(pidl, szPath))
        return FALSE;


    HighestPriority = 101;
    IconIndex = NumIconOverlayHandlers;
    for(Index = 0; Index < NumIconOverlayHandlers; Index++)
    {
        hResult = Handlers[Index]->IsMemberOf(szPath, SFGAO_FILESYSTEM);
        if (hResult == S_OK)
        {
            hResult = Handlers[Index]->GetPriority(&Priority);
            if (hResult == S_OK)
            {
                if (Priority < HighestPriority)
                {
                    HighestPriority = Priority;
                    IconIndex = Index;
                }
            }
        }
    }

    if (IconIndex == NumIconOverlayHandlers)
        return FALSE;

    hResult = Handlers[IconIndex]->GetOverlayInfo(wTemp, MAX_PATH, pIndex, &Flags);

    if (hResult == S_OK)
        return TRUE;
    else
        return FALSE;
}