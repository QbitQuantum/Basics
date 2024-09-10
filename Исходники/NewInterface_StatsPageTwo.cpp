DWORD STDCALL mouseNewStatsPageTwoLeftDown(sWinMessage* msg)
{
	if (!D2isLODGame()) return -1;

	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();
	if (!isOnStatsPage(x,y)) return 1;

	if (isOnCloseBtn(x,y))
	{
		log_msg("push down left button close\n");
		isDownBtn.close = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnPreviousPageBtn(x,y))
	{
		log_msg("push down left button previous page\n");
		isDownBtn.previousPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnNextPageBtn(x,y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
	}

	freeMessage(msg);
	return 0;
}