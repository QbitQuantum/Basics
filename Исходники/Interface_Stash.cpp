DWORD STDCALL manageBtnDown(sWinMessage* msg)
{
	if (onRealm || !D2isLODGame()) return 0;

	if (isOnButtonPreviousStash(msg->x,msg->y))
		isDownBtn.previous = 1;
	else if (isOnButtonNextStash(msg->x,msg->y))
		isDownBtn.next = 1;
	else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x,msg->y))
		isDownBtn.toggleToSharedStash = 1;
	else if (isOnButtonPreviousIndexStash(msg->x,msg->y))
		isDownBtn.previousIndex = 1;
	else if (isOnButtonNextIndexStash(msg->x,msg->y))
		isDownBtn.nextIndex = 1;
	else if (active_sharedGold && isOnButtonPutGold(msg->x,msg->y))
		isDownBtn.putGold = 1;
	else if (active_sharedGold && isOnButtonTakeGold(msg->x,msg->y))
		isDownBtn.takeGold = 1;
	else return 0;

	D2PlaySound(4,0,0,0,0);
	freeMessage(msg);
	return 1;
}