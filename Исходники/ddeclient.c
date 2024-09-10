/******************************************************************
 *		WDML_HandleUnadviseReply
 *
 *
 */
static WDML_QUEUE_STATE WDML_HandleUnadviseReply(WDML_CONV* pConv, MSG* msg, WDML_XACT* pXAct, DWORD *ack)
{
    DDEACK	ddeAck;
    UINT_PTR	uiLo, uiHi;
    HSZ		hsz;

    if (msg->message != WM_DDE_ACK || WIN_GetFullHandle((HWND)msg->wParam) != pConv->hwndServer)
    {
	return WDML_QS_PASS;
    }

    UnpackDDElParam(WM_DDE_ACK, msg->lParam, &uiLo, &uiHi);
    hsz = WDML_MakeHszFromAtom(pConv->instance, uiHi);

    if (DdeCmpStringHandles(hsz, pXAct->hszItem) != 0)
	return WDML_QS_PASS;

    FreeDDElParam(WM_DDE_ACK, msg->lParam);
    GlobalDeleteAtom(uiHi);

    if (ack) *ack = uiLo;
    WDML_ExtractAck(uiLo, &ddeAck);

    TRACE("WM_DDE_ACK received while waiting for a timeout\n");

    if (!ddeAck.fAck)
    {
	TRACE("Returning FALSE on XTYP_ADVSTOP - fAck was FALSE\n");
        pXAct->hDdeData = NULL;
    }
    else
    {
	/* billx: remove the link */
	WDML_RemoveLink(pConv->instance, (HCONV)pConv, WDML_CLIENT_SIDE,
			pXAct->hszItem, pXAct->wFmt);
        pXAct->hDdeData = (HDDEDATA)1;
    }
    return WDML_QS_HANDLED;
}