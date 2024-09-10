void CPlayerPlaylistBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl != IDC_PLAYLIST) {
        return;
    }

    int nItem = lpDrawItemStruct->itemID;
    CRect rcItem = lpDrawItemStruct->rcItem;
    POSITION pos = FindPos(nItem);
    bool fSelected = pos == m_pl.GetPos();
    CPlaylistItem& pli = m_pl.GetAt(pos);

    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    if (!!m_list.GetItemState(nItem, LVIS_SELECTED)) {
        FillRect(pDC->m_hDC, rcItem, CBrush(0xf1dacc));
        FrameRect(pDC->m_hDC, rcItem, CBrush(0xc56a31));
    } else {
        FillRect(pDC->m_hDC, rcItem, CBrush(GetSysColor(COLOR_WINDOW)));
    }

    COLORREF textcolor = fSelected ? 0xff : 0;
    if (pli.m_fInvalid) {
        textcolor |= 0xA0A0A0;
    }

    CString time = !pli.m_fInvalid ? m_list.GetItemText(nItem, COL_TIME) : _T("Invalid");
    CSize timesize(0, 0);
    CPoint timept(rcItem.right, 0);
    if (time.GetLength() > 0) {
        timesize = pDC->GetTextExtent(time);
        if ((3 + timesize.cx + 3) < rcItem.Width() / 2) {
            timept = CPoint(rcItem.right - (3 + timesize.cx + 3), (rcItem.top + rcItem.bottom - timesize.cy) / 2);

            pDC->SetTextColor(textcolor);
            pDC->TextOut(timept.x, timept.y, time);
        }
    }

    CString fmt, file;
    fmt.Format(_T("%%0%dd. %%s"), (int)log10(0.1 + m_pl.GetCount()) + 1);
    file.Format(fmt, nItem + 1, m_list.GetItemText(nItem, COL_NAME));
    CSize filesize = pDC->GetTextExtent(file);
    while (3 + filesize.cx + 6 > timept.x && file.GetLength() > 3) {
        file = file.Left(file.GetLength() - 4) + _T("...");
        filesize = pDC->GetTextExtent(file);
    }

    if (file.GetLength() > 3) {
        pDC->SetTextColor(textcolor);
        pDC->TextOut(rcItem.left + 3, (rcItem.top + rcItem.bottom - filesize.cy) / 2, file);
    }
}