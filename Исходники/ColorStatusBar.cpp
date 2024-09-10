void CColorStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    int	iPane = lpDrawItemStruct->itemID;
    if (!(GetPaneStyle(iPane) & SBPS_DISABLED)) {
        CWnd	*pParentWnd = GetParent();
        ASSERT(pParentWnd != NULL);	// parent window must exist
        // get pane's background color from parent window
        COLORREF	BkColor = (COLORREF)pParentWnd->SendMessage(
                                  UWM_COLORSTATUSBARPANE, WPARAM(lpDrawItemStruct->hDC), iPane);
        CDC dc;
        dc.Attach(lpDrawItemStruct->hDC);	// attach CDC object to device context
        CRect	r(&lpDrawItemStruct->rcItem);
        dc.FillSolidRect(r, BkColor);
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextAlign(TA_CENTER);
        dc.TextOut(r.left + r.Width() / 2, r.top, GetPaneText(iPane));
        // must detach CDC object from device context, otherwise device
        // context would be destroyed when CDC object goes out of scope
        dc.Detach();
    }
}