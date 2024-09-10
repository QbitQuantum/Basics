void CFoldView::OnSubfold()
{
	
	//User has chosen the SubFold menu option	
	CMenu* menu = GetFoldDocument()->menuframe->GetMenu( );	

	subfold = !subfold;

	if (subfold) menu->CheckMenuItem(ID_SUBFOLD,MF_CHECKED);
	else menu->CheckMenuItem(ID_SUBFOLD,MF_UNCHECKED); 


}