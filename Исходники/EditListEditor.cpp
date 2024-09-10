void CEditListEditor::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl != IDC_EDITLIST) {
        return;
    }

    int nItem = lpDrawItemStruct->itemID;
    CRect rcItem = lpDrawItemStruct->rcItem;
    POSITION pos = m_editList.FindIndex(nItem);

    if (pos) {
        bool fSelected = (pos == m_curPos);
        UNREFERENCED_PARAMETER(fSelected);
        CClip& curClip = m_editList.GetAt(pos);
        CString strTemp;

        CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

        if (!!m_list.GetItemState(nItem, LVIS_SELECTED)) {
            FillRect(pDC->m_hDC, rcItem, CBrush(0xf1dacc));
            FrameRect(pDC->m_hDC, rcItem, CBrush(0xc56a31));
        } else {
            FillRect(pDC->m_hDC, rcItem, CBrush(GetSysColor(COLOR_WINDOW)));
        }

        COLORREF textcolor = RGB(0, 0, 0);
        if (!curClip.HaveIn() || !curClip.HaveOut()) {
            textcolor = RGB(255, 0, 0);
        }

        for (int i = 0; i < COL_MAX; i++) {
            m_list.GetSubItemRect(nItem, i, LVIR_LABEL, rcItem);
            pDC->SetTextColor(textcolor);
            switch (i) {
                case COL_INDEX:
                    strTemp.Format(_T("%d"), nItem + 1);
                    pDC->DrawText(strTemp, rcItem, DT_CENTER | DT_VCENTER);
                    break;
                case COL_IN:
                    pDC->DrawText(curClip.GetIn(), rcItem, DT_CENTER | DT_VCENTER);
                    break;
                case COL_OUT:
                    pDC->DrawText(curClip.GetOut(), rcItem, DT_CENTER | DT_VCENTER);
                    break;
                case COL_NAME:
                    pDC->DrawText(curClip.GetName(), rcItem, DT_LEFT | DT_VCENTER);
                    break;
            }
        }
    }
}