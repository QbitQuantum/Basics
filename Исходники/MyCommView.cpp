void CMyCommView::OnBtsendkey() 
{
    // TODO: Add your control notification handler code here
    CRect rect;
    CPoint point;
    CButton * mybt = (CButton *)GetDlgItem(IDC_BTSENDKEY);
    mybt->GetWindowRect(rect);
    point.x = rect.right;
    point.y = rect.bottom;

    CMenu menu;
    VERIFY( menu.LoadMenu( IDR_MENU_SNEDKEY ) );
    CMenu* popup = menu.GetSubMenu(0);
    ASSERT( popup != NULL );
            popup->TrackPopupMenu(TPM_RIGHTALIGN| TPM_RIGHTBUTTON, point.x, point.y, this ); 
}