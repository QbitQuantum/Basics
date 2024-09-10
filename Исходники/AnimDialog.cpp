void AnimDialog::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	if(pMenu)
	{
		UINT state = pMenu->GetMenuState( ID_VIEW_ANIMATIONDIALOG, MF_BYCOMMAND );
		if( state == 0xFFFFFFFF )
			return;

		pMenu->CheckMenuItem(ID_VIEW_ANIMATIONDIALOG, MF_UNCHECKED | MF_BYCOMMAND);
	}

	CDialog::OnClose();
}