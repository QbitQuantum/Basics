WINMON_API BOOL Winmon_DeskWndPainted(RECT *dskRt)
{
	BOOL ret = dskWndPainted;
	dskWndPainted = FALSE;

	if (dskRt != NULL) {
		WaitForSingleObject(hSem, INFINITE);
		CopyRect(dskRt, &dskWndPaintedRect);
		SetRectEmpty(&dskWndPaintedRect);
		ReleaseSemaphore(hSem, 1, NULL);
	}

	return ret;
}