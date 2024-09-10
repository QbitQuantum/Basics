void CGameAI::doSale()
{
	RECT rect = {0};
	int goodsCounter = 0;
	int times = 0;
	BOOL done = FALSE;
	int tmp = 0;
	int currX = 0;
	int currY = 0;
	makeSureLocation();
	writeLog(TEXT("出售魔石"));

	while(!done && isAIStart)
	{
		++times;
		rightClickTager(script.targetX, script.targetY);
		Sleep(TALK_INTERVAL/2);
		fuckingMouse();
		Sleep(TALK_INTERVAL/2);
		tmp = leader->getScreen()->colorDeviation(&SALE_CONDITION, RGB(255,255,255));
		if(tmp >=30 && tmp < 50)
		{
			CSystem::leftClick(&SALE_CONDITION);
			Sleep(TALK_INTERVAL);
		} 
		else if (tmp < 30 && tmp > 5)
		{
			CSystem::leftClick(&SALE_CONDITION2);
			Sleep(TALK_INTERVAL);
		}

		for(int i = 0; i < LOOP_TIMES; ++i) 
		{
			if(leader->getScreen()->locate(IDB_ALL, &rect, &SALE_ALL_CONDITION))
			{
				TRACE("Found Sale all\n");
				CSystem::leftClick(&rect);
				Sleep(TALK_INTERVAL);
				for( int x = 0; x < LOOP_TIMES; ++x)
				{
					if(leader->getScreen()->locate(IDB_SURE, &rect, &SALE_SURE_CONDITION))
					{
						TRACE("Found sale sure\n");
						CSystem::leftClick(&rect);
						Sleep(TALK_INTERVAL);
					}
					if(leader->getScreen()->locate(IDB_YES, &rect, &SALE_YES_CONDITION))
					{
						TRACE("Found sale yes\n");
						CSystem::leftClick(&rect);
						Sleep(TALK_INTERVAL);
						break;
					}
					Sleep(TALK_INTERVAL);
				}
				checkGoods(&goodsCounter);
				if(goodsCounter < 10)
				{
					done = TRUE;
					break;
				}
			} 
			if(leader->getScreen()->locate(IDB_CANCEL, &rect, &SALE_CANCEL_CONDITION))
			{
				TRACE("Found Sale Cancel\n");
				CSystem::leftClick(&rect);
				Sleep(TALK_INTERVAL);
			} 
			if(leader->getScreen()->colorDeviation(&NOT_SALE_CONDITION, RGB(255,255,255)) > 5)
			{
				CSystem::leftClick(&NOT_SALE_CONDITION);
				Sleep(TALK_INTERVAL);
				done = TRUE;
				break;
			} else if(leader->getScreen()->colorDeviation(&NOT_SALE_CONDITION2, RGB(255,255,255)) > 5)
			{
				CSystem::leftClick(&NOT_SALE_CONDITION2);
				Sleep(TALK_INTERVAL);
				done = TRUE;
				break;
			}
			Sleep(TALK_INTERVAL);
		}
	}
	writeLog(TEXT("出售魔石完成"));
	fuckingNP();
}