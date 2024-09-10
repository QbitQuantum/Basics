LRESULT CHilighterManageDlg::OnNMCustomdrawList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
    AtlTrace(L"drawstage: %u\n", pNMCD->nmcd.dwDrawStage);
    if (pNMCD->nmcd.dwDrawStage == CDDS_PREPAINT)
    {
        return CDRF_NOTIFYITEMDRAW;
    }
    if (pNMCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
    {
        return CDRF_NOTIFYSUBITEMDRAW;
    }
    if (pNMCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
    {
        if (pNMCD->iSubItem == 1)
        {
            int index = static_cast<int>(pNMCD->nmcd.dwItemSpec);
            if (index < m_list.GetItemCount())
            {
                hilighter& hl = GetHilighter(index);
                pNMCD->clrText = hl.d.color;
                pNMCD->clrTextBk = hl.d.bkcolor;
            }
        }
    }
    return CDRF_DODEFAULT;
}