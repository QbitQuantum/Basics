BOOL WINAPI _export BLExtTextOut(HDC hDC,
                                 int x,
                                 int y,
                                 UINT fuOpt,
                                 const RECT FAR* lprc,
                                 LPCSTR lpStr,
                                 UINT cbLen,
                                 int FAR* lpDx)
{
	POINT pt ;
	HWND hWDC ;
	HWND hWPT ;
	
#ifdef _DEBUG
    DbgPrintf("NhWSrh.DLL     BLExtTextOut Begin");
    DbgPrintf("NhWSrh.DLL     BLExtTextOut hDC: %d, x: %d, y: %d, fuOpt: %d, cbLen: %d", 
        	  hDC,
        	  x,
        	  y,
        	  fuOpt,
        	  cbLen);
#endif
        // restore the old textout.
        RestoreWinApi(&g_ExtTextOutHook);
    
	//Added by XGL, Nov 3rd, 1998
	//We cannot get corret word with Explorer as background window
	//in Windows98, so this situation must be dealt with.
	pt.x = g_CurMousePos.x; pt.y = g_CurMousePos.y ;
	hWDC = WindowFromDC(hDC) ;
	hWPT = WindowFromPoint(pt) ;

	if (hWDC == NULL || hWPT == hWDC
		|| IsParentOrSelf(hWPT, hWDC)
		|| IsParentOrSelf(hWDC, hWPT))
	{
	//Adding ends. XGL, Nov 3rd, 1998

		if ((g_bAllowGetCurWord) && (!IsBadReadPtr(lpStr, cbLen)) && (cbLen > 0))
        {
                g_nTextAlign = GetTextAlign(hDC);
                g_nExtra     = GetTextCharacterExtra(hDC);
                GetCurrentPositionEx(hDC, &g_CurPos);
                GetTextMetrics(hDC, &g_tm);
///////////////////////////////////////////////////////////////////////////
// Modify by Yan/Gang 1997/11/18
// 用於修改在计算 TA_CENTER 情况的失误。
	g_dwDCOrg = 0;
		bRecAllRect = FALSE;
		GetStringRect(hDC, (LPSTR)lpStr, cbLen, x, y, &g_rcTotalRect, lpDx);
		bRecAllRect = TRUE;
// End Modify
///////////////////////////////////////////////////////////////////////////

                if ((WindowFromDC != NULL)&&(WindowFromDC(hDC) == NULL))
                {
#ifdef _DEBUG
                        DbgPrintf("NhWSrh.DLL     BLTextOut WindowFromDC() == NULL");
                        DbgLPCSTR("NhWSrh.DLL     BLTextOut: ", (LPSTR)lpStr, cbLen, TRUE);
#endif
                        // 赋零，用於避免MEMDC对串位置的影响·
                        g_dwDCOrg = 0;
                        
                        AddToTextOutBuffer(hDC, (LPSTR)lpStr, cbLen, x, y, lpDx);
                }
                else
                {
#ifdef _DEBUG
                        DbgPrintf("NhWSrh.DLL     BLTextOut WindowFromDC() != NULL");
                        DbgLPCSTR("NhWSrh.DLL     BLTextOut: ", (LPSTR)lpStr, cbLen, TRUE);
#endif
                        g_dwDCOrg    = GetDCOrg(hDC);
        
                        GetCurMousePosWord(hDC, (LPSTR)lpStr, cbLen, x, y, lpDx);
                }
		}
		else
		{
#ifdef _DEBUG
			DbgPrintf("NhWSrh.DLL     BLExtTextOut ((!g_bAllowGetCurWord) || (IsBadReadPtr(lpStr, cbLen)) && (cbLen <= 0))");
			if (!g_bAllowGetCurWord)
			{
				DbgPrintf("NhWSrh.DLL     BLExtTextOut !g_bAllowGetCurWord");
			}
			if (IsBadReadPtr(lpStr, cbLen))
			{
				DbgPrintf("NhWSrh.DLL     BLExtTextOut IsBadReadPtr()");
			}
			if (cbLen <= 0)
			{
				DbgPrintf("NhWSrh.DLL     BLExtTextOut cbLen <= 0");
			}
#endif
		}
    }
        // call old textout.
        ExtTextOut(hDC, x, y, fuOpt, lprc, lpStr, cbLen, lpDx);
        HookWinApi(&g_ExtTextOutHook, ONLYHOOK);
#ifdef _DEBUG
        DbgPrintf("NhWSrh.DLL     BLExtTextOut End");
#endif
        return (TRUE);
}         