BOOL PASCAL TV_SortCB(PTREE pTree, TV_SORTCB FAR *pSortCB, BOOL bRecurse,
        PFNDPACOMPARE lpfnDPACompare)
{
        HDPA dpaSort;
        HDSA dsaCmp;
        HTREEITEM hItem, hNext, hFirstMoved;
        LPTVCOMPARE psCompare, FAR *ppsCompare;
        int i, cKids;
        HTREEITEM hParent = pSortCB->hParent;

#ifdef DEBUG
        DWORD dwTime = GetTickCount();
        nCompares = 0;
#endif

        if (!hParent || hParent == TVI_ROOT)
            hParent = pTree->hRoot;

        // Code below assumes at least one kid
        cKids = TV_CountKids(hParent);
        if (!cKids)
            return FALSE;

        // Create a DSA for all the extra info we'll need
        dsaCmp = DSA_Create(sizeof(TVCOMPARE), cKids);
        if (!dsaCmp)
            goto Error1;

        // Create a DPA containing all the tree items
        dpaSort = DPA_Create(cKids);
        if (!dpaSort)
            goto Error2;

        for (hItem = hParent->hKids; hItem; hItem = hItem->hNext)
        {
                TVCOMPARE sCompare;
                int nItem;

                // If I can't sort all of them, I don't want to sort any of them

                // We want to cache the text callback for default processing
                if (!lpfnDPACompare && hItem->lpstr==LPSTR_TEXTCALLBACK)
                {
                        TV_ITEM sItem;
                        TCHAR szTemp[MAX_PATH];

                        sItem.pszText = szTemp;
                        sItem.cchTextMax  = ARRAYSIZE(szTemp);
                        TV_GetItem(pTree, hItem, TVIF_TEXT, &sItem);

                        sCompare.lpstr = NULL;
                        sCompare.bCallBack = TRUE;
                        Str_Set(&sCompare.lpstr, sItem.pszText);
                        if (!sCompare.lpstr)
                        {
                                goto Error3;
                        }
                }
                else
                {
                        sCompare.lpstr = hItem->lpstr;
                        sCompare.bCallBack = FALSE;
                }

                // Create the pointer for this guy and add it to the DPA list
                sCompare.hItem = hItem;
                nItem = DSA_InsertItem(dsaCmp, 0x7fff, &sCompare);
                if (nItem < 0)
                {
                        if (sCompare.bCallBack)
                        {
                                Str_Set(&sCompare.lpstr, NULL);
                        }
                        goto Error3;
                }

                if (DPA_InsertPtr(dpaSort, 0x7fff, DSA_GetItemPtr(dsaCmp, nItem)) < 0)
                {
                        goto Error3;
                }
        }

        // Sort the DPA, then stick them back under the parent in the new order
        DPA_Sort(dpaSort, lpfnDPACompare ? (PFNDPACOMPARE)lpfnDPACompare :
                 (PFNDPACOMPARE) TV_DefCompare, (LPARAM)pSortCB);


        // Look for the first moved item, so we can invalidate a smaller area
        ppsCompare = (LPTVCOMPARE FAR *)DPA_GetPtrPtr(dpaSort);
        if (hParent->hKids != (*ppsCompare)->hItem)
        {
                hParent->hKids = (*ppsCompare)->hItem;
                hFirstMoved = hParent->hKids;
        }
        else
        {
                hFirstMoved = NULL;
        }

        // We do n-1 iterations here
        for (i = DPA_GetPtrCount(dpaSort) - 1; i > 0; --i, ++ppsCompare)
        {
                hNext = (*(ppsCompare+1))->hItem;
                if ((*ppsCompare)->hItem->hNext != hNext && !hFirstMoved)
                {
                        hFirstMoved = hNext;
                }
                (*ppsCompare)->hItem->hNext = hNext;
        }
        (*ppsCompare)->hItem->hNext = NULL;

        TV_UpdateShownIndexes(pTree, hParent);
        if ((pSortCB->hParent == TVI_ROOT) || !hParent) {
            if (pTree->cShowing < pTree->cFullVisible) {
                pTree->hTop = pTree->hRoot->hKids;
            }
        }

        if (hFirstMoved && (hParent->state & TVIS_EXPANDED))
        {
                RECT rcUpdate;

                TV_GetItemRect(pTree, hFirstMoved, &rcUpdate, FALSE);
                if (hParent->hNext)
                {
                        RECT rcTemp;

                        TV_GetItemRect(pTree, hParent->hNext, &rcTemp, FALSE);
                        rcUpdate.bottom = rcTemp.bottom;
                }
                else
                {
                        RECT rcClient;
                        GetClientRect(pTree->ci.hwnd, &rcClient);
                        // Set to maximal positive number, so the whole rest of
                        // the treeview gets invalidated
                        rcUpdate.bottom = rcClient.bottom;
                }
                if (pTree->fRedraw)
                    InvalidateRect(pTree->ci.hwnd, &rcUpdate, TRUE);
        }

Error3:
        DPA_Destroy(dpaSort);
Error2:
        for (i = DSA_GetItemCount(dsaCmp) - 1; i >= 0; --i)
        {
                psCompare = DSA_GetItemPtr(dsaCmp, i);
                if (psCompare->bCallBack)
                {
                        Str_Set(&(psCompare->lpstr), NULL);
                }
        }
        DSA_Destroy(dsaCmp);
Error1:

#ifdef DEBUG
        DebugMsg(DM_TRACE, TEXT("tv.sort: %ld ms; %d cmps"), GetTickCount()-dwTime, nCompares);
#endif

    {
        int wNewPos;
        // restore the scroll position
        if (GetWindowStyle(pTree->ci.hwnd) & WS_VSCROLL) {
            SCROLLINFO si;

            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_POS;
            wNewPos = 0;
            if (GetScrollInfo(pTree->ci.hwnd, SB_VERT, &si)) {
                wNewPos = si.nPos;
            }

        } else {
            wNewPos = 0;
        }

        if (TV_SetTopItem(pTree, wNewPos))
            UpdateWindow(pTree->ci.hwnd);
    }

    // if the caret is the child of the thing that was sorted, make sure it's
    // visible (but if we're sorting something completely unrelated, don't bother
    if (pTree->hCaret) {
        hItem = pTree->hCaret;
        do {
            // do this first.  if hParent is hCaret, we don't want to ensure visible...
            // only if it's an eventual child
            hItem = hItem->hParent;
            if (hParent == hItem) {
                TV_EnsureVisible(pTree, pTree->hCaret);
            }
        } while(hItem && hItem != pTree->hRoot);
    }

    return TRUE;
}