static BOOL IsNewWindow(HWND hWnd)
{
	BOOL isNewWindow=FALSE;

	EnterCriticalSection(&g_cs);

	if(!FindWindowIndex(hWnd,NULL))
	{
		if(g_numHWNDs==g_maxNumHWNDs)
		{
			if(g_maxNumHWNDs==0)
			{
				g_maxNumHWNDs=16;
				g_pHWNDs=LocalAlloc(0,g_maxNumHWNDs*sizeof *g_pHWNDs);
			}
			else
			{
				g_maxNumHWNDs+=g_maxNumHWNDs/2;
				g_pHWNDs=LocalReAlloc(g_pHWNDs,g_maxNumHWNDs*sizeof *g_pHWNDs,0);
			}
		}

		g_pHWNDs[g_numHWNDs++]=hWnd;
	}

	LeaveCriticalSection(&g_cs);

	return isNewWindow;
}