static int
ProcShapeSelectInput(ClientPtr client)
{
    REQUEST(xShapeSelectInputReq);
    WindowPtr pWin;
    ShapeEventPtr pShapeEvent, pNewShapeEvent, *pHead;
    XID clientResource;
    int rc;

    REQUEST_SIZE_MATCH(xShapeSelectInputReq);
    rc = dixLookupWindow(&pWin, stuff->window, client, DixReceiveAccess);
    if (rc != Success)
        return rc;
    rc = dixLookupResourceByType((pointer *) &pHead, pWin->drawable.id,
                                 ShapeEventType, client, DixWriteAccess);
    if (rc != Success && rc != BadValue)
        return rc;

    switch (stuff->enable) {
    case xTrue:
        if (pHead) {

            /* check for existing entry. */
            for (pShapeEvent = *pHead;
                 pShapeEvent; pShapeEvent = pShapeEvent->next) {
                if (pShapeEvent->client == client)
                    return Success;
            }
        }

        /* build the entry */
        pNewShapeEvent = malloc(sizeof(ShapeEventRec));
        if (!pNewShapeEvent)
            return BadAlloc;
        pNewShapeEvent->next = 0;
        pNewShapeEvent->client = client;
        pNewShapeEvent->window = pWin;
        /*
         * add a resource that will be deleted when
         * the client goes away
         */
        clientResource = FakeClientID(client->index);
        pNewShapeEvent->clientResource = clientResource;
        if (!AddResource(clientResource, ClientType, (pointer) pNewShapeEvent))
            return BadAlloc;
        /*
         * create a resource to contain a pointer to the list
         * of clients selecting input.  This must be indirect as
         * the list may be arbitrarily rearranged which cannot be
         * done through the resource database.
         */
        if (!pHead) {
            pHead = malloc(sizeof(ShapeEventPtr));
            if (!pHead ||
                !AddResource(pWin->drawable.id, ShapeEventType,
                             (pointer) pHead)) {
                FreeResource(clientResource, RT_NONE);
                return BadAlloc;
            }
            *pHead = 0;
        }
        pNewShapeEvent->next = *pHead;
        *pHead = pNewShapeEvent;
        break;
    case xFalse:
        /* delete the interest */
        if (pHead) {
            pNewShapeEvent = 0;
            for (pShapeEvent = *pHead; pShapeEvent;
                 pShapeEvent = pShapeEvent->next) {
                if (pShapeEvent->client == client)
                    break;
                pNewShapeEvent = pShapeEvent;
            }
            if (pShapeEvent) {
                FreeResource(pShapeEvent->clientResource, ClientType);
                if (pNewShapeEvent)
                    pNewShapeEvent->next = pShapeEvent->next;
                else
                    *pHead = pShapeEvent->next;
                free(pShapeEvent);
            }
        }
        break;
    default:
        client->errorValue = stuff->enable;
        return BadValue;
    }
    return Success;
}