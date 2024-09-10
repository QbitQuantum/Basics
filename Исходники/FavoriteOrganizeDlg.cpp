void CFavoriteOrganizeDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl != IDC_LIST2) {
        return;
    }

    int nItem = lpDrawItemStruct->itemID;
    CRect rcItem = lpDrawItemStruct->rcItem;

    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    if (!!m_list.GetItemState(nItem, LVIS_SELECTED)) {
        CBrush b1, b2;
        b1.CreateSolidBrush(0xf1dacc);
        pDC->FillRect(rcItem, &b1);
        b2.CreateSolidBrush(0xc56a31);
        pDC->FrameRect(rcItem, &b2);
    } else {
        CBrush b;
        b.CreateSysColorBrush(COLOR_WINDOW);
        pDC->FillRect(rcItem, &b);
    }

    CString str;
    pDC->SetTextColor(0);

    str = m_list.GetItemText(nItem, 0);
    pDC->TextOut(rcItem.left + 3, (rcItem.top + rcItem.bottom - pDC->GetTextExtent(str).cy) / 2, str);
    str = m_list.GetItemText(nItem, 1);
    if (!str.IsEmpty()) {
        pDC->TextOut(rcItem.right - pDC->GetTextExtent(str).cx - 3, (rcItem.top + rcItem.bottom - pDC->GetTextExtent(str).cy) / 2, str);
    }
}