LRESULT formview::OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    CMenu formviewmenu;
    const POINT point = {LOWORD(lParam), HIWORD(lParam)};
    formviewmenu.LoadMenuA(IDR_LISTVIEWMENU);

    {
        LVITEMA item;
        CMenuHandle listviewmenu = formviewmenu.GetSubMenu(1);
        if(this->listview_m.GetSelectedItem(&item))
        {
            listviewmenu.SetMenuDefaultItem(ID_POPUP_OPEN);
            listviewmenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, *this);
            return 0;
        }
    }
    {
        CRect rect;
        this->listview_m.GetWindowRect(&rect);
        CMenuHandle listviewmenu = formviewmenu.GetSubMenu(0);
        if(rect.PtInRect(point))
            listviewmenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, *this);
    }

    return 0;
}