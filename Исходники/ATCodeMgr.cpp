int CATCodeMgr::GetAllLoadedModules( PMODULEENTRY32 pRetBuf, int maxCnt )
{
    int curCnt = 0;

    // 반환 버퍼 초기화
    ZeroMemory(pRetBuf, sizeof(PMODULEENTRY32)*maxCnt);

    // 프로세스 스냅샷 핸들을 생성
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
    if(INVALID_HANDLE_VALUE == hModuleSnap) return 0;

    pRetBuf[curCnt].dwSize = sizeof(MODULEENTRY32);
    BOOL bExist = Module32First(hModuleSnap, &pRetBuf[curCnt]);

    while( bExist == TRUE && curCnt < maxCnt )
    {
        curCnt++;
        pRetBuf[curCnt].dwSize = sizeof(MODULEENTRY32);
        bExist = Module32Next(hModuleSnap, &pRetBuf[curCnt]);
    }

    CloseHandle (hModuleSnap);

    return curCnt;
}