void asteroid_editor::OnInitMenu(CMenu* pMenu)
{
	int i;
	CString str;
	CMenu *m;

	m = pMenu->GetSubMenu(0);
	clear_menu(m);
	i = 0; //for (i=0; i<MAX_ASTEROID_FIELDS; i++) {
		str.Format("Asteroid Field %d", i);
		m->AppendMenu(MF_ENABLED | MF_STRING, ID_FIELD_MENU + i, str);
	//}

	m->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);
	if (cur_field != -1)
		m->CheckMenuItem(ID_FIELD_MENU + cur_field, MF_BYCOMMAND | MF_CHECKED);

	CDialog::OnInitMenu(pMenu);
}