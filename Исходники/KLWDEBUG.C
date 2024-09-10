void PEXPORT KlwPop(BOOL bDisplay)
{
    GLOBALHANDLE hCtx, hPrev, hWatches;
    WORD active, i;
  
    if (hWndStack)
    {
        SendMessage(hWndStack, LB_DELETESTRING, 0, 0L);
        SendMessage(hWndStack, LB_SETCURSEL, 0, 0L);
    }
    
    if (varstack)
    {
        if (varstack->pops)
            varstack->pops--;
        else
        {
            GLOBALHANDLE hPrev = varstack->hPrev;
            GLOBALHANDLE hCtx = varstack->hCtx;
            
            if (varstack->idVarList)
                KppDeleteList(varstack->idVarList);
            GLOBALUNLOCK(hCtx);
            GLOBALFREE(hCtx);
            
            if (hPrev)
                varstack = (varctx) GLOBALLOCK(hPrev);
            else
                varstack = NULL;
            
            if (varstack)
                KlwUpdateWatches(varstack->lpBody, varstack->idVarList);
        }
    }        

    if (!dbgstack)
        return;
    
    if (dbgstack->pops)
    {
        dbgstack->pops--;
        return;
    }
    
    for (i = 0; i < MAX_WATCHES; ++i) {
        watch wtc = &dbgstack->wtcs[i];
        
        if (!wtc->bPerm)
        {
            if (wtc->idSlot)
            {
                LPSLOT lpSlot = (LPSLOT) KppGetItem(SLOT, wtc->idSlot);
            
                if (lpSlot)
                {
                    SLOTFLAGS(lpSlot) &= ~SLOTWATCHED;
                    KppReleaseItem(SLOT, wtc->idSlot);
                }
            }
        
            if (wtc->idNames)
                KppDeleteList(wtc->idNames);
        }
    }
        
    hCtx = dbgstack->hCtx;
    hPrev = dbgstack->hPrev;
    hWatches = dbgstack->hWatches;
    active = dbgstack->active;
    if (dbgstack->hWatches)
        SetWindowText(hWndWatches, "");
    
    if (hPrev)
    {
        dbgctx ctx = (dbgctx) GLOBALLOCK(hPrev);
        
        KlwTransferWatches(dbgstack, ctx);
        dbgstack = ctx;

        if (active == CTX_ABORT)
            ctx->active = CTX_ABORT;
        else if (bDisplay && ctx->active == CTX_STEP)
        {
            KlwShowExp(hWndSource, ctx->wType, ctx->idCode, ctx->idObj);
            ShowCurLine(hWndSource, NULL, FALSE);
            if (ctx->hWatches)
            {
                LPSTR lpWatches = GLOBALLOCK(ctx->hWatches);
                
                SetWindowText(hWndWatches, lpWatches);
                GLOBALUNLOCK(ctx->hWatches);
            }
        }
    }        
    else
    {
        HMENU hMenu = GetMenu(hWndKalView);
        
        EnableMenuItem(hMenu, KLW_CLEAR, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMenu, KLW_STACK, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu, KLW_SELECTION, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu, KLW_WTCSEL, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMenu, KLW_WTCSLOT, MF_BYCOMMAND | MF_GRAYED); 
        EnableMenuItem(hMenu, KLW_RUN, MF_BYCOMMAND | MF_ENABLED); 
        EnableMenuItem(hMenu, KLW_CLOSE, MF_BYCOMMAND | MF_ENABLED);
        GetSystemMenu(hWndKalView, TRUE);

        dbgstack = NULL;
        SendMessage(hWndSource, EM_SETSEL, 0, 0L);
        ShowWindow(hWndStack, SW_HIDE);
    }
    
    GLOBALUNLOCK(hCtx);
    GLOBALFREE(hCtx);
    if (hWatches)
        GLOBALFREE(hWatches);
}