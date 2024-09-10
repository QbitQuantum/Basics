void CListCtrlComboBox::ShowEdit(int nItem,int nSubItem) {
    if (nItem < 0 || nSubItem < 0) return;
    if (m_pParentList == NULL) return ;
    CListCtrl *pCtrl = m_pParentList;
    CRect rect;
    m_pParentList = pCtrl;
//	m_pParentList->GetSubItemRect(nItem,nIndex,LVIR_LABEL,rcCtrl);

    // 列可见
    CHeaderCtrl* pHeader = (CHeaderCtrl*)pCtrl->GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if( nSubItem >= nColumnCount || pCtrl->GetColumnWidth(nSubItem) < 5 )
        return ;

    // 列偏移
    int offset = 0;
    for( int i = 0; i < nSubItem; i++ )
        offset += pCtrl->GetColumnWidth( i );

    pCtrl->GetItemRect( nItem, &rect, LVIR_BOUNDS );
    rect.top -= 2;
    if (rect.top < 0) rect.top = 0;
    // 滚动列，便于操作
    CRect rcClient;
    CSize size;
    pCtrl->GetClientRect( &rcClient );
//	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
    if( offset + rect.left < 0 ) {
        size.cx = offset + rect.left;
        size.cy = 0;
        pCtrl->Scroll( size );
        rect.left -= size.cx;
    } else if(offset + rect.left > rcClient.right ) {
        size.cx = offset + rect.left;
        size.cy = 0;
        pCtrl->Scroll( size );
        rect.left -= size.cx;
    }
    // 获取列的对齐方式
    LV_COLUMN lvcol;
    lvcol.mask = LVCF_FMT;
    pCtrl->GetColumn( nSubItem, &lvcol );
    DWORD dwStyle;
    if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
        dwStyle = ES_LEFT;
    else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
        dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    rect.left += offset + 1;
    if (nSubItem > 0)
        rect.right = rect.left + pCtrl->GetColumnWidth( nSubItem );
    else
        rect.right = rect.left + pCtrl->GetColumnWidth( nSubItem );

    if( rect.right > rcClient.right)
        rect.right = rcClient.right;

    rect.bottom = rect.top + 12 * rect.Height();

    CString strItem = pCtrl->GetItemText(nItem,nSubItem);
    pCtrl->ClientToScreen(rect);
    GetParent()->ScreenToClient(rect);
    MoveWindow(rect);
//	SetWindowPos(NULL, rect.left,rect.top,rect.Width(),rect.Height(), SWP_SHOWWINDOW);
//	pCtrl->ClientToScreen(rcClient);
//	GetParent()->ScreenToClient(rcClient);
//	pCtrl->SetWindowPos(this, rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(), SWP_SHOWWINDOW);
    ShowWindow(SW_SHOW);
    SetWindowText(strItem);
    ::SetFocus(GetSafeHwnd());
    SetItemHeight(-1,13);
//设置对应选项
    int nIndex =  FindStringExact(0, strItem);
    if (nIndex < 0) nIndex = 0;
    SetCurSel(nIndex);
    m_nCurrentItem = nItem;
    m_nCurrentSubItem = nSubItem;
}