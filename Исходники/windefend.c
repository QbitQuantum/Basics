/*
* wdCheckEmulatedVFS
*
* Purpose:
*
* Detect Microsoft Security Engine emulation by it own VFS artefact.
*
* Microsoft AV provides special emulated environment for scanned application where it
* fakes general system information, process environment structures/data to make sure
* API calls are transparent for scanned code. It also use simple Virtual File System
* allowing this AV track file system changes and if needed continue emulation on new target.
*
* This method implemented in commercial malware presumable since 2013.
*
*/
VOID wdCheckEmulatedVFS(
    VOID
)
{
    WCHAR szBuffer[MAX_PATH];
    WCHAR szMsEngVFS[12] = { L':', L'\\', L'm', L'y', L'a', L'p', L'p', L'.', L'e', L'x', L'e', 0 };

    RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
    GetModuleFileName(NULL, szBuffer, MAX_PATH);
    if (_strstri(szBuffer, szMsEngVFS) != NULL) {
        ExitProcess((UINT)0);
    }
}