//Hook TextOutA的过程
DLLEXPORT BOOL WINAPI NHExtTextOutA(HDC hdc,
                                    int X,	//当前需要绘制的文本的起始位置
                                    int Y,
                                    UINT fuOptions,
                                    CONST RECT *lprc,
                                    LPCTSTR lpString,
                                    UINT cbCount,
                                    CONST INT *lpDx)
{
    POINT pt;
    HWND  hWDC;
    HWND  hWPT;
    DWORD dwThreadIdWithPoint = 0;
    DWORD dwThreadIdCurr = 0;

    // restore
    RestoreWin32Api(&g_ExtTextOutAHook, HOOK_NEED_CHECK);
    /*
    	if (cbCount != 0)
    	{
    		char cBuffer[0x100];
    		wsprintf(cBuffer, "-> NHExtTextOutA : %s (%s) (%d)\n", "start", lpString, cbCount);
    		OutputDebugString(cBuffer);
    	}
    */
    //DbgFilePrintf("-> NHExtTextOutA : lpString(%s), cbCount(%d)\n", lpString, cbCount);

    pt.x = g_CurMousePos.x;
    pt.y = g_CurMousePos.y;
    hWDC = WindowFromDC(hdc);
    hWPT = WindowFromPoint(pt);

    dwThreadIdWithPoint = GetWindowThreadProcessId(hWPT, NULL);
    dwThreadIdCurr = GetCurrentThreadId();

    if(dwThreadIdWithPoint == dwThreadIdCurr)
    {
        if (hWDC == NULL || hWPT == hWDC
                || IsParentOrSelf(hWPT, hWDC)
                || IsParentOrSelf(hWDC, hWPT))
        {
            if ((g_bAllowGetCurWord) && (!IsBadReadPtr(lpString, cbCount))
                    && (cbCount > 0))
            {
                g_nTextAlign = GetTextAlign(hdc);
                g_nExtra     = GetTextCharacterExtra(hdc);
                GetCurrentPositionEx(hdc, &g_CurPos);
                GetTextMetrics(hdc, &g_tm);
                g_dwDCOrg.x = 0;
                g_dwDCOrg.y = 0;
                bRecAllRect = FALSE;
                //findword.c中的代码,取出当前字符的矩形范围
                GetStringRect(hdc, (LPSTR)lpString, cbCount, X, Y,
                              &g_rcTotalRect, lpDx);
                bRecAllRect = TRUE;

                if ((WindowFromDC != NULL)&&(WindowFromDC(hdc) == NULL))
                {
                    g_dwDCOrg.x = 0;
                    g_dwDCOrg.y = 0;

                    AddToTextOutBuffer(hdc, (LPSTR)lpString, cbCount,
                                       X, Y, lpDx);
                }
                else
                {
                    GetDCOrgEx(hdc, &g_dwDCOrg);

                    //findword.c中的代码,取出当前位置下的单词
                    GetCurMousePosWord(hdc, (LPSTR)lpString, cbCount,
                                       X, Y, lpDx);
                }
            }
        }
    }
    // call ExtTextOutA
    ExtTextOutA(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);

    HookWin32Api(&g_ExtTextOutAHook, HOOK_NEED_CHECK);

    return TRUE;
}