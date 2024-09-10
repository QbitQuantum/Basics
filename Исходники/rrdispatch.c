static int
ProcRRSelectInput (ClientPtr client)
{
    REQUEST(xRRSelectInputReq);
    rrClientPriv(client);
    RRTimesPtr	pTimes;
    WindowPtr	pWin;
    RREventPtr	pRREvent, *pHead;
    XID		clientResource;
    int		rc;

    REQUEST_SIZE_MATCH(xRRSelectInputReq);
    rc = dixLookupWindow(&pWin, stuff->window, client, DixReceiveAccess);
    if (rc != Success)
	return rc;
    rc = dixLookupResourceByType((pointer *)&pHead, pWin->drawable.id,
				 RREventType, client, DixWriteAccess);
    if (rc != Success && rc != BadValue)
	return rc;

    if (stuff->enable & (RRScreenChangeNotifyMask|
			 RRCrtcChangeNotifyMask|
			 RROutputChangeNotifyMask|
			 RROutputPropertyNotifyMask)) 
    {
	ScreenPtr	pScreen = pWin->drawable.pScreen;
	rrScrPriv	(pScreen);

	pRREvent = NULL;
	if (pHead) 
	{
	    /* check for existing entry. */
	    for (pRREvent = *pHead; pRREvent; pRREvent = pRREvent->next)
		if (pRREvent->client == client)
		    break;
	}

	if (!pRREvent)
	{
	    /* build the entry */
	    pRREvent = (RREventPtr) malloc(sizeof (RREventRec));
	    if (!pRREvent)
		return BadAlloc;
	    pRREvent->next = 0;
	    pRREvent->client = client;
	    pRREvent->window = pWin;
	    pRREvent->mask = stuff->enable;
	    /*
	     * add a resource that will be deleted when
	     * the client goes away
	     */
	    clientResource = FakeClientID (client->index);
	    pRREvent->clientResource = clientResource;
	    if (!AddResource (clientResource, RRClientType, (pointer)pRREvent))
		return BadAlloc;
	    /*
	     * create a resource to contain a pointer to the list
	     * of clients selecting input.  This must be indirect as
	     * the list may be arbitrarily rearranged which cannot be
	     * done through the resource database.
	     */
	    if (!pHead)
	    {
		pHead = (RREventPtr *) malloc(sizeof (RREventPtr));
		if (!pHead ||
		    !AddResource (pWin->drawable.id, RREventType, (pointer)pHead))
		{
		    FreeResource (clientResource, RT_NONE);
		    return BadAlloc;
		}
		*pHead = 0;
	    }
	    pRREvent->next = *pHead;
	    *pHead = pRREvent;
	}
	/*
	 * Now see if the client needs an event
	 */
	if (pScrPriv && (pRREvent->mask & RRScreenChangeNotifyMask))
	{
	    pTimes = &((RRTimesPtr) (pRRClient + 1))[pScreen->myNum];
	    if (CompareTimeStamps (pTimes->setTime, 
				   pScrPriv->lastSetTime) != 0 ||
		CompareTimeStamps (pTimes->configTime, 
				   pScrPriv->lastConfigTime) != 0)
	    {
		RRDeliverScreenEvent (client, pWin, pScreen);
	    }
	}
    }
    else if (stuff->enable == 0) 
    {
	/* delete the interest */
	if (pHead) {
	    RREventPtr pNewRREvent = 0;
	    for (pRREvent = *pHead; pRREvent; pRREvent = pRREvent->next) {
		if (pRREvent->client == client)
		    break;
		pNewRREvent = pRREvent;
	    }
	    if (pRREvent) {
		FreeResource (pRREvent->clientResource, RRClientType);
		if (pNewRREvent)
		    pNewRREvent->next = pRREvent->next;
		else
		    *pHead = pRREvent->next;
		free(pRREvent);
	    }
	}
    }
    else 
    {
	client->errorValue = stuff->enable;
	return BadValue;
    }
    return Success;
}