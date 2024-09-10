/***********************************************************************
 *      SetupPromptForDiskA (SETUPAPI.@)
 */
UINT WINAPI SetupPromptForDiskA(HWND hwndParent, PCSTR DialogTitle, PCSTR DiskName,
        PCSTR PathToSource, PCSTR FileSought, PCSTR TagFile, DWORD DiskPromptStyle,
        PSTR PathBuffer, DWORD PathBufferSize, PDWORD PathRequiredSize)
{
    WCHAR *DialogTitleW, *DiskNameW, *PathToSourceW;
    WCHAR *FileSoughtW, *TagFileW, PathBufferW[MAX_PATH];
    UINT ret, length;

    TRACE("%p, %s, %s, %s, %s, %s, 0x%08x, %p, %d, %p\n", hwndParent, debugstr_a(DialogTitle),
          debugstr_a(DiskName), debugstr_a(PathToSource), debugstr_a(FileSought),
          debugstr_a(TagFile), DiskPromptStyle, PathBuffer, PathBufferSize,
          PathRequiredSize);

    DialogTitleW = strdupAtoW(DialogTitle);
    DiskNameW = strdupAtoW(DiskName);
    PathToSourceW = strdupAtoW(PathToSource);
    FileSoughtW = strdupAtoW(FileSought);
    TagFileW = strdupAtoW(TagFile);

    ret = SetupPromptForDiskW(hwndParent, DialogTitleW, DiskNameW, PathToSourceW,
            FileSoughtW, TagFileW, DiskPromptStyle, PathBufferW, MAX_PATH, PathRequiredSize);

    HeapFree(GetProcessHeap(), 0, DialogTitleW);
    HeapFree(GetProcessHeap(), 0, DiskNameW);
    HeapFree(GetProcessHeap(), 0, PathToSourceW);
    HeapFree(GetProcessHeap(), 0, FileSoughtW);
    HeapFree(GetProcessHeap(), 0, TagFileW);

    if(ret == DPROMPT_SUCCESS)
    {
        length = WideCharToMultiByte(CP_ACP, 0, PathBufferW, -1, NULL, 0, NULL, NULL);
        if(PathRequiredSize) *PathRequiredSize = length;
        if(PathBuffer)
        {
            if(length > PathBufferSize)
                return DPROMPT_BUFFERTOOSMALL;
            WideCharToMultiByte(CP_ACP, 0, PathBufferW, -1, PathBuffer, length, NULL, NULL);
        }
    }
    return ret;
}