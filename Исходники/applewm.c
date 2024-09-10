static int
ProcAppleWMSelectInput (register ClientPtr client)
{
    REQUEST(xAppleWMSelectInputReq);
    WMEventPtr      pEvent, pNewEvent, *pHead;
    XID             clientResource;
    int             i;

    REQUEST_SIZE_MATCH (xAppleWMSelectInputReq);
    i = dixLookupResourceByType((pointer *)&pHead, eventResource, EventType, client, DixWriteAccess);
    if (stuff->mask != 0) {
        if (i == Success && pHead) {
            /* check for existing entry. */
            for (pEvent = *pHead; pEvent; pEvent = pEvent->next)
            {
                if (pEvent->client == client)
                {
                    pEvent->mask = stuff->mask;
                    updateEventMask (pHead);
                    return Success;
                }
            }
        }

        /* build the entry */
        pNewEvent = (WMEventPtr) xalloc (sizeof (WMEventRec));
        if (!pNewEvent)
            return BadAlloc;
        pNewEvent->next = 0;
        pNewEvent->client = client;
        pNewEvent->mask = stuff->mask;
        /*
         * add a resource that will be deleted when
         * the client goes away
         */
        clientResource = FakeClientID (client->index);
        pNewEvent->clientResource = clientResource;
        if (!AddResource (clientResource, ClientType, (pointer)pNewEvent))
            return BadAlloc;
        /*
         * create a resource to contain a pointer to the list
         * of clients selecting input.  This must be indirect as
         * the list may be arbitrarily rearranged which cannot be
         * done through the resource database.
         */
        if (i != Success || !pHead)
        {
            pHead = (WMEventPtr *) xalloc (sizeof (WMEventPtr));
            if (!pHead ||
                    !AddResource (eventResource, EventType, (pointer)pHead))
            {
                FreeResource (clientResource, RT_NONE);
                return BadAlloc;
            }
            *pHead = 0;
        }
        pNewEvent->next = *pHead;
        *pHead = pNewEvent;
        updateEventMask (pHead);
    } else if (stuff->mask == 0) {
        /* delete the interest */
        if (i == Success && pHead) {
            pNewEvent = 0;
            for (pEvent = *pHead; pEvent; pEvent = pEvent->next) {
                if (pEvent->client == client)
                    break;
                pNewEvent = pEvent;
            }
            if (pEvent) {
                FreeResource (pEvent->clientResource, ClientType);
                if (pNewEvent)
                    pNewEvent->next = pEvent->next;
                else
                    *pHead = pEvent->next;
                xfree (pEvent);
                updateEventMask (pHead);
            }
        }
    } else {
        client->errorValue = stuff->mask;
        return BadValue;
    }
    return Success;
}