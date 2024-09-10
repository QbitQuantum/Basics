//##ModelId=4095FA7D00FA
void look::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	    CMenu menu;            // top-level menu 
		CMenu *pMenu=NULL;  // pop-up menu 

		menu.LoadMenu(IDR_MENU2); 
		pMenu = menu.GetSubMenu(0);
		if (!pMenu)
			return ;

		POINT pt;
		GetCursorPos(&pt);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL); 
		menu.DestroyMenu(); 
	*pResult = 0;
}