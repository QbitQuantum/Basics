LRESULT CALLBACK APCWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_NULL: 
		while (APCCallQueue.getCount())
		{
			APCCall tmpCall;

			WaitForSingleObject(hApcMutex, INFINITE);
			if (APCCallQueue.getCount())
			{
				tmpCall = APCCallQueue[0];
				APCCallQueue.remove(0);
			}
			ReleaseMutex(hApcMutex);
			if (tmpCall.func) tmpCall.func(tmpCall.param);
		}
		SleepEx(0, TRUE); // process APCs created by plugins that do not use core service
		break;

	case WM_TIMECHANGE:
		RecalculateTime();
		break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}