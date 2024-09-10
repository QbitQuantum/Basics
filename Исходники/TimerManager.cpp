void TimerManager::Update()
{
	int tick = GetTickCount();

	TimerNode* pNode = m_head->next;


	std::vector<TimerNode*> l;

	while(pNode)
	{

		if((tick - pNode->start_tick) < pNode->interval)
		{
			break;
		}

		TimerNode* pTmp = pNode;

		pNode = pNode->next;


		pTmp->handler(pTmp, pTmp->interval, pTmp->handler_context);
		

		UnLink(pTmp);

		l.push_back(pTmp);

	}

	for(size_t i = 0; i <l.size(); ++i)
	{
		InsertNode(l[i]);
	}

}