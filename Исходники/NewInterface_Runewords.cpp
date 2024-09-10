DWORD STDCALL mouseRunewordsPageLeftUp(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x,msg->y)) return 1;

	if (isOnCloseBtn(msg->x,msg->y))
	{
		log_msg("push up left button close\n");
		if (isDownBtn.close)
			D2TogglePage(2,1,0);
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoStatPage(GetCurrentPage()+1);
			log_msg("next page press\n");
		}
	}
	else if (isOnPrevRunesBtn(msg->x,msg->y))
	{
		log_msg("push up left button prev runes\n");
		if (isDownBtn.prevRunes)
		{
			if (curRunesPage) curRunesPage--;
		}
	}
	else if (isOnNextRunesBtn(msg->x,msg->y))
	{
		log_msg("push up left button next runes\n");
		if (isDownBtn.nextRunes)
		{
			if (curRunesPage < maxRunesPage) curRunesPage++;
		}
	}

	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all=0;
	return 0;
}