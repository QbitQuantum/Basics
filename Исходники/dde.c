/****************************************************************************
 *                                                                          *
 *  FUNCTION   : DdeCallback()                                              *
 *                                                                          *
 *  PURPOSE    : This handles all callbacks from the DDEML.  This handles   *
 *               updating of the associated conversation and any special    *
 *               testing cases such as blocking callbacks etc.              *
 *                                                                          *
 *               For the most part, clients only handle advise data and     *
 *               asynchronous transaction completion here.                  *
 *                                                                          *
 *  RETURNS    : Results vary depending on transaction type.                *
 *                                                                          *
 ****************************************************************************/
HDDEDATA EXPENTRY DdeCallback(
WORD wType,
WORD wFmt,
HCONV hConv,
HSZ hsz1,
HSZ hsz2,
HDDEDATA hData,
DWORD lData1,
DWORD lData2)
{
    HWND hwnd;
    CONVINFO ci;
    XACT *pxact;

    if (hConv) {
        /*
         * update conversation status if it changed.
         */
        MYCONVINFO *pmci;
        
        ci.cb = sizeof(CONVINFO);
	if (!DdeQueryConvInfo(hConv,(DWORD) QID_SYNC, &ci) || (!IsWindow((HWND)ci.hUser))) {
            /*
             * This conversation does not yet have a corresponding MDI window
             * or is disconnected.
             */
            return 0;
        }
        if (pmci = (MYCONVINFO *)GetWindowWord((HWND)ci.hUser, 0)) {
            if (pmci->ci.wStatus != ci.wStatus ||
                    pmci->ci.wConvst != ci.wConvst ||
                    pmci->ci.wLastError != ci.wLastError) {
                /*
                 * Things have changed, updated the conversation window.
                 */
                InvalidateRect((HWND)ci.hUser, NULL, TRUE);
            }
            if (ci.wConvst & ST_INLIST) {
                /*
                 * update the associated list window (if any) as well.
                 */
                if (hwnd = FindListWindow(ci.hConvList))
                    InvalidateRect(hwnd, NULL, TRUE);
            }
        }
    }

    /*
     * handle special block on next callback option here.  This demonstrates
     * the CBR_BLOCK feature.
     */
    if (fBlockNextCB && !(wType & XTYPF_NOBLOCK)) {
        fBlockNextCB = FALSE;
        return(CBR_BLOCK);
    }

    /*
     * handle special termination here.  This demonstrates that at any time
     * a client can drop a conversation.
     */
    if (fTermNextCB && hConv && wType != XTYP_DISCONNECT) {
        fTermNextCB = FALSE;
        MyDisconnect(hConv);
        return(0);
    }

    /*
     * Now we begin sort out what to do.
     */
    switch (wType) {
    case XTYP_REGISTER:
    case XTYP_UNREGISTER:
        /*
         * This is where the client would insert code to keep track of
         * what servers are available.  This could cause the initiation
         * of some conversations.
         */
        break;

    case XTYP_DISCONNECT:
        if (fAutoReconnect) {
            /*
             * attempt a reconnection
             */
            if (hConv = DdeReconnect(hConv)) {
                AddConv(ci.hszServiceReq, ci.hszTopic, hConv, FALSE);
                return 0;
            }
        }
        
        /*
         * update conv window to show its new state.
         */
        SendMessage((HWND)ci.hUser, UM_DISCONNECTED, 0, 0);
        return 0;
        break;

    case XTYP_ADVDATA:
        /*
         * data from an active advise loop (from a server)
         */
        Delay(wDelay);
        hwnd = FindAdviseChild((HWND)ci.hUser, hsz2, wFmt);
        if (!IsWindow(hwnd)) {
            PSTR pszItem, pszFmt;
            /*
             * AdviseStart window is gone, make a new one.
             */
            pxact = (XACT *)MyAlloc(sizeof(XACT));
            pxact->wType = wType;
            pxact->hConv = hConv;
            pxact->wFmt = wFmt;
            pxact->hszItem = hsz2;
            DdeKeepStringHandle(idInst, hsz2);
            
            pszItem = GetHSZName(hsz2);
            pszFmt = GetFormatName(wFmt);
            
            hwnd = CreateInfoCtrl(NULL, 
                    (int)SendMessage((HWND)ci.hUser, UM_GETNEXTCHILDX, 0, 0L),
                    (int)SendMessage((HWND)ci.hUser, UM_GETNEXTCHILDY, 0, 0L),
                    200, 100,
                    (HWND)ci.hUser, hInst,
                    Type2String(wType, 0), (LPSTR)pszItem, NULL,
                    NULL, (LPSTR)pszFmt, NULL,
                    ICSTY_SHOWFOCUS, 0, (DWORD)(LPSTR)pxact);
                    
            MyFree(pszFmt);
            MyFree(pszItem);

            if (!IsWindow(hwnd))
                return(DDE_FNOTPROCESSED); 
        }
        if (!hData) {
            /*
             * XTYPF_NODATA case - request the info. (we do this synchronously
             * for simplicity)
             */
            hData = DdeClientTransaction(NULL, 0L, hConv, hsz2, wFmt,
                    XTYP_REQUEST, DefTimeout, NULL);
        }
        if (hData) {
            PSTR pData;
            /*
             * Show incomming data on corresponding transaction window.
             */
            pData = GetTextData(hData);
            SendMessage(hwnd, ICM_SETSTRING, ICSID_CENTER, (DWORD)(LPSTR)pData);
            MyFree(pData);
            DdeFreeDataHandle(hData);
        }
        SendMessage(hwnd, ICM_SETSTRING, ICSID_LL, (DWORD)(LPSTR)"Advised");
        return(DDE_FACK);
        break;
        
    case XTYP_XACT_COMPLETE:
        /*
         * An asynchronous transaction has completed.  Show the results.
         *
         * ...unless the XOPT_BLOCKRESULT is chosen.
         */
        
        ci.cb = sizeof(CONVINFO);
        if (DdeQueryConvInfo(hConv, lData1, &ci) &&
                IsWindow((HWND)ci.hUser) && 
                (pxact = (XACT *)GetWindowWord((HWND)ci.hUser, GWW_WUSER))) {
                
            if (pxact->fsOptions & XOPT_BLOCKRESULT) {
                pxact->fsOptions &= ~XOPT_BLOCKRESULT;
                return(CBR_BLOCK);
            }
            
            pxact->Result = lData2;
            pxact->ret = hData;
            CompleteTransaction((HWND)ci.hUser, pxact);
        }
        break;
    }
}