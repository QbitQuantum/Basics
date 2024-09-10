BOOL GUIAPI SubtractClipRect (PCLIPRGN pRgn, const RECT* pRect)
{
    PCLIPRECT pCRect, pSaved, pTemp;
    RECT rc[4], rcTemp, rcInflated;
    int nCount;
    PRECT src, erc;
    int i;

    if (IsRectEmpty (pRect))
        return FALSE;

    rcInflated = *pRect;
    erc = &rcInflated;

    NormalizeRect (erc);

    if (!DoesIntersect(&pRgn->rcBound, erc)) {
        return FALSE;
    }

    pCRect = pRgn->head;
    while (pCRect) {

        src = &pCRect->rc;
        if (!IntersectRect(&rcTemp, src, erc)) {
            pCRect = pCRect->next;
            continue;
        }

        pSaved = pCRect->next;

        nCount = 0;
        if(erc->top > src->top)
        {
            rc[nCount].left  = src->left;
            rc[nCount].top   = src->top;
            rc[nCount].right = src->right;
            rc[nCount].bottom = erc->top;
            nCount++;

            src->top = erc->top;
        }

        if(erc->bottom < src->bottom)
        {
            rc[nCount].top  = erc->bottom;
            rc[nCount].left   = src->left;
            rc[nCount].right = src->right;
            rc[nCount].bottom = src->bottom;
            nCount++;
 
            src->bottom = erc->bottom;
        }

        if(erc->left > src->left)
        {
            rc[nCount].left  = src->left;
            rc[nCount].top   = src->top;
            rc[nCount].right = erc->left;
            rc[nCount].bottom = src->bottom;
            nCount++;
        }

        if(erc->right < src->right)
        {
            rc[nCount].left  = erc->right;
            rc[nCount].top   = src->top;
            rc[nCount].right = src->right;
            rc[nCount].bottom = src->bottom;
            nCount++;
        }

        if (nCount == 0)
            SetRectEmpty (&pCRect->rc);
        else if(nCount > 0)
            pCRect->rc = rc[0];

        for(i = 1; i<nCount; i++)
        {
            pTemp = ClipRectAlloc (pRgn->heap); 
            pTemp->rc = rc[i];
            pCRect->next = pTemp;
            pCRect = pTemp;
        }

        pCRect->next = pSaved;

        pCRect = pSaved;
    }

    EvaluateBoundRect (pRgn);

    return TRUE;
}