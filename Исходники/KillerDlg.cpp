// 处理列表框右键消息 弹出浮动菜单
void CKillerDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->iItem != -1)
	{
	  DWORD dwPos = GetMessagePos();// 得到鼠标坐标
      CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
      CMenu menu;
      VERIFY( menu.LoadMenu(IDR_MENU1));
      CMenu* popup = menu.GetSubMenu(0);
      ASSERT( popup != NULL );
	  //确定弹出式菜单的位置
      popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	  //资源回收
		HMENU hmenu=menu.Detach();
		menu.DestroyMenu();
   }
	*pResult = 0;
	*pResult = 0;
}