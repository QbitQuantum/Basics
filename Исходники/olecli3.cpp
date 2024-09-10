void COleClientItem::Activate(LONG nVerb, CView* pView, LPMSG lpMsg)
{
    ASSERT_VALID(this);
    ASSERT(m_lpObject != NULL);
    if (pView != NULL)
        ASSERT_VALID(pView);
    if (lpMsg != NULL)
        ASSERT(AfxIsValidAddress(lpMsg, sizeof(MSG), FALSE));

    // store the container HWND for in place activation then do the verb
    if (m_pView == NULL)
        m_pView = pView;

    _AFX_OLE_STATE* pOleState = _afxOleState;
    CView* pViewSave = pOleState->m_pActivateView;
    pOleState->m_pActivateView = NULL;

    // get item rectangle for in-place players
    //  (that may not support in-place activation)
    LPCRECT lpPosRect = NULL;
    CRect rectPos;
    if (pView != NULL)
    {
        ASSERT_VALID(pView);
        rectPos.SetRectEmpty();
        OnGetItemPosition(rectPos);
        if (!rectPos.IsRectEmpty())
        {
            lpPosRect = &rectPos;
            pOleState->m_pActivateView = pView;
        }
    }

    // prepare DoVerb parameters and call into the server
    LPOLECLIENTSITE lpClientSite = GetClientSite();
    HWND hWnd = pView->GetSafeHwnd();
    SCODE sc = m_lpObject->DoVerb(nVerb, lpMsg, lpClientSite, -1,
                                  hWnd, lpPosRect);

    pOleState->m_pActivateView = pViewSave;

    // clear out m_pView in case in-place activation only partially worked
    if (!IsInPlaceActive())
        m_pView = NULL;

    // update available status based on the results of DoVerb
    //  (this is used in the links dialog).
    m_bLinkUnavail = (BYTE)FAILED(sc);

    CheckGeneral(sc);
}