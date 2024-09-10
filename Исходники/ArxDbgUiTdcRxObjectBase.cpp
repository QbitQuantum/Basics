void
ArxDbgUiTdcRxObjectBase::buildColumns(CListCtrl& dataList)
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    dataList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 2;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Field");
    lvc.iSubItem = 0;
    dataList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    dataList.InsertColumn(1, &lvc);
}