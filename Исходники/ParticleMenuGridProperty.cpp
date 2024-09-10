void CParticleMenuGridProperty::OnRClickValue(CPoint C,BOOL B)
{
	CPoint pt;
	GetCursorPos(&pt);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,MENU_USE_SELECTED_TEXTURE,"Use Selected Texture");
	CString texturePath;
	if(((CMainFrame*)AfxGetMainWnd())->GetSelectedResourceTexture(texturePath))
		menu.EnableMenuItem(MENU_USE_SELECTED_TEXTURE,MF_BYCOMMAND|MF_ENABLED);
	else
		menu.EnableMenuItem(MENU_USE_SELECTED_TEXTURE,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	menu.TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,m_pWndList->GetParent());
}