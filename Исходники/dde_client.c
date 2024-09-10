/******************************************************************
 *		WDML_HandleRequestReply
 *
 *
 */
static WDML_QUEUE_STATE WDML_HandleRequestReply(WDML_CONV* pConv, MSG* msg, WDML_XACT* pXAct, DWORD *ack)
{
    DDEACK		ddeAck;
    WINE_DDEHEAD	wdh;
    UINT_PTR		uiLo, uiHi;
    HSZ			hsz;

    if (WIN_GetFullHandle((HWND)msg->wParam) != pConv->hwndServer)
	return WDML_QS_PASS;

    switch (msg->message)
    {
    case WM_DDE_ACK:
        UnpackDDElParam(WM_DDE_ACK, msg->lParam, &uiLo, &uiHi);
        FreeDDElParam(WM_DDE_ACK, msg->lParam);
	GlobalDeleteAtom(uiHi);
       if (ack) *ack = uiLo;
	WDML_ExtractAck(uiLo, &ddeAck);
	pXAct->hDdeData = 0;
	if (ddeAck.fAck)
	    ERR("Positive answer should appear in NACK for a request, assuming negative\n");
	TRACE("Negative answer...\n");
	break;

    case WM_DDE_DATA:
        UnpackDDElParam(WM_DDE_DATA, msg->lParam, &uiLo, &uiHi);
	TRACE("Got the result (%08lx)\n", uiLo);

	hsz = WDML_MakeHszFromAtom(pConv->instance, uiHi);

	if (DdeCmpStringHandles(hsz, pXAct->hszItem) != 0)
	    return WDML_QS_PASS;

	pXAct->hDdeData = WDML_Global2DataHandle((HGLOBAL)uiLo, &wdh);
	if (wdh.fRelease)
	{
	    GlobalFree((HGLOBAL)uiLo);
	}
	if (wdh.fAckReq)
	{
	    pConv->instance->lastError = DMLERR_MEMORY_ERROR;
	}
	else
	{
	    GlobalDeleteAtom(uiHi);
            FreeDDElParam(WM_DDE_ACK, msg->lParam);
	}
	break;

    default:
        FreeDDElParam(msg->message, msg->lParam);
	return WDML_QS_PASS;
    }

    return WDML_QS_HANDLED;
}