CListBox* CPlayerListCtrl::ShowInPlaceListBox(int nItem, int nCol, CAtlList<CString>& lstItems, int nSel)
{
    CRect rect;
    if (!PrepareInPlaceControl(nItem, nCol, rect)) {
        return nullptr;
    }

    DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL/*|WS_HSCROLL*/ | LBS_NOTIFY;
    CListBox* pListBox = DEBUG_NEW CInPlaceListBox(nItem, nCol, lstItems, nSel);
    pListBox->Create(dwStyle, rect, this, IDC_LIST1);

    CRect ir;
    GetItemRect(m_nItemClicked, &ir, LVIR_BOUNDS);

    pListBox->SetItemHeight(-1, ir.Height());

    CDC* pDC = pListBox->GetDC();
    CFont* pWndFont = GetFont();
    pDC->SelectObject(pWndFont);
    int width = GetColumnWidth(nCol);
    POSITION pos = lstItems.GetHeadPosition();
    while (pos) {
        int w = pDC->GetTextExtent(lstItems.GetNext(pos)).cx + 16;
        if (width < w) {
            width = w;
        }
    }
    ReleaseDC(pDC);

    CRect r;
    pListBox->GetWindowRect(r);
    ScreenToClient(r);
    r.top = ir.bottom;
    r.bottom = r.top + pListBox->GetItemHeight(0) * (pListBox->GetCount() + 1);
    r.right = r.left + width;
    pListBox->MoveWindow(r);

    m_fInPlaceDirty = false;

    return pListBox;
}