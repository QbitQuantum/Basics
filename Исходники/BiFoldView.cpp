void CBiFoldView::OnForceForbidunimolecularpairs()
{
	//User has chosen the forbid unimolecular pair menu option
	CMenu* menu = GetBiFoldDocument()->menuframe->GetMenu( );	

	forbidunimolecular = !forbidunimolecular;

	if (forbidunimolecular) menu->CheckMenuItem(ID_FORCE_FORBIDUNIMOLECULARPAIRS,MF_CHECKED);
	else menu->CheckMenuItem(ID_FORCE_FORBIDUNIMOLECULARPAIRS,MF_UNCHECKED); 

	
}