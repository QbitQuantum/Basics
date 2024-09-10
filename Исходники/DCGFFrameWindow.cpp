void CDCGFFrameWindow::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			CMenu* cmenu = 
				CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
			
			if(m_Menu.IsMenu(cmenu)||m_DefaultMenu.IsMenu(cmenu)){
				m_Menu.MeasureItem(lpMeasureItemStruct);
				setflag=TRUE;
			}
		}
	}
	
	if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);	
}