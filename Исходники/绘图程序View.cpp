void CMyView::OnContextMenu(CWnd*, CPoint point)
{

    // CG: This block was added by the Pop-up Menu component
    {
        if (point.x == -1 && point.y == -1) {
            //keystroke invocation
            CRect rect;
            GetClientRect(rect);
            ClientToScreen(rect);

            point = rect.TopLeft();
            point.Offset(5, 5);
        }

        CMenu menu;
        VERIFY(menu.LoadMenu(CG_IDR_POPUP_MY_VIEW));

        CMenu* pPopup = menu.GetSubMenu(0);
        ASSERT(pPopup != NULL);
        CWnd* pWndPopupOwner = this;

        while (pWndPopupOwner->GetStyle() & WS_CHILD)
            pWndPopupOwner = pWndPopupOwner->GetParent();

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
                               pWndPopupOwner);
    }

}