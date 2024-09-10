void CTextureFontGeneratorDlg::OnOptionsExportstroketemplates()
{
	CMenu *pMenu = GetMenu();
	int Checked = pMenu->GetMenuState(ID_OPTIONS_EXPORTSTROKETEMPLATES, 0) & MF_CHECKED;
	Checked ^= MF_CHECKED;
	pMenu->CheckMenuItem( ID_OPTIONS_EXPORTSTROKETEMPLATES, Checked );
}