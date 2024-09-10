int NEAR ListView_SItemHitTest(LV* plv, int x, int y, UINT FAR* pflags)
{

    int iHit;
    UINT flags;
    POINT pt;
    RECT rcState;
    RECT rcLabel;
    RECT rcIcon;


    // Map window-relative coordinates to view-relative coords...
    //
    pt.x = x + plv->ptOrigin.x;
    pt.y = y + plv->ptOrigin.y;

    // If we find an uncomputed item, recompute them all now...
    //
    if (plv->rcView.left == RECOMPUTE)
        ListView_Recompute(plv);

    flags = 0;

    if (ListView_IsOwnerData( plv ))
    {
        int cSlots;
        POINT ptWnd;
        LISTITEM item;

        cSlots = ListView_GetSlotCount( plv, TRUE );
        iHit = ListView_CalcHitSlot( plv, pt, cSlots );
        ListView_SGetRectsOwnerData( plv, iHit, &rcIcon, &rcLabel, &item, FALSE );
        ptWnd.x = x;
        ptWnd.y = y;

        if (PtInRect(&rcIcon, ptWnd))
        {
            flags = LVHT_ONITEMICON;
        }
        else if (PtInRect(&rcLabel, ptWnd))
        {
            flags = LVHT_ONITEMLABEL;
        }
    }
    else
    {
        for (iHit = 0; iHit < ListView_Count(plv); iHit++)
        {
            LISTITEM FAR* pitem = ListView_FastGetZItemPtr(plv, iHit);
            POINT ptItem;

            ptItem.x = pitem->pt.x;
            ptItem.y = pitem->pt.y;

            rcIcon.top    = ptItem.y;
            rcIcon.bottom = ptItem.y + plv->cyItem;

            rcLabel.top    = rcIcon.top;
            rcLabel.bottom = rcIcon.bottom;

            // Quick, easy rejection test...
            //
            if (pt.y < rcIcon.top || pt.y >= rcIcon.bottom)
                continue;

            rcIcon.left   = ptItem.x;
            rcIcon.right  = ptItem.x + plv->cxSmIcon;
            
            rcState.bottom = rcIcon.bottom;
            rcState.right = rcIcon.left;
            rcState.left = rcState.right - plv->cxState;
            rcState.top = rcState.bottom - plv->cyState;

            rcLabel.left   = rcIcon.right;
            rcLabel.right  = rcLabel.left + pitem->cxSingleLabel;

            if (PtInRect(&rcIcon, pt))
            {
                flags = LVHT_ONITEMICON;
            } else if (PtInRect(&rcLabel, pt))
            {
                flags = LVHT_ONITEMLABEL;
            } else if (PtInRect(&rcState, pt)) 
            {
                flags = LVHT_ONITEMSTATEICON;
            }
            
            if (flags)
                break;
        }
    }

    if (flags == 0)
    {
        flags = LVHT_NOWHERE;
        iHit = -1;
    }
    else
    {
      if (!ListView_IsOwnerData( plv ))
          iHit = DPA_GetPtrIndex(plv->hdpa, (void FAR*)ListView_FastGetZItemPtr(plv, iHit));
    }

    *pflags = flags;
    return iHit;
}