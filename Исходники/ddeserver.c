/******************************************************************
 *		WDML_ServerHandleRequest
 *
 *
 */
static	WDML_QUEUE_STATE WDML_ServerHandleRequest(WDML_CONV* pConv, WDML_XACT* pXAct)
{
    HDDEDATA		hDdeData = 0;
    BOOL		fAck = TRUE;

    if (!(pConv->instance->CBFflags & CBF_FAIL_REQUESTS))
    {

	hDdeData = WDML_InvokeCallback(pConv->instance, XTYP_REQUEST, pXAct->wFmt, (HCONV)pConv,
				       pConv->hszTopic, pXAct->hszItem, 0, 0, 0);
    }

    switch ((ULONG_PTR)hDdeData)
    {
    case 0:
	TRACE("No data returned from the Callback\n");
	fAck = FALSE;
	break;

    case (ULONG_PTR)CBR_BLOCK:
	return WDML_QS_BLOCK;

    default:
        {
	    HGLOBAL	hMem = WDML_DataHandle2Global(hDdeData, TRUE, FALSE, FALSE, FALSE);
	    if (!PostMessageW(pConv->hwndClient, WM_DDE_DATA, (WPARAM)pConv->hwndServer,
			      ReuseDDElParam(pXAct->lParam, WM_DDE_REQUEST, WM_DDE_DATA,
					     (UINT_PTR)hMem, (UINT_PTR)pXAct->atom)))
	    {
                pConv->instance->lastError = DMLERR_POSTMSG_FAILED;
		DdeFreeDataHandle(hDdeData);
		GlobalFree(hMem);
		fAck = FALSE;
	    }
	}
	break;
    }

    WDML_PostAck(pConv, WDML_SERVER_SIDE, 0, FALSE, fAck, pXAct->atom, pXAct->lParam, WM_DDE_REQUEST);

    WDML_DecHSZ(pConv->instance, pXAct->hszItem);

    return WDML_QS_HANDLED;
}