void CLoadPortalFileDialog::OnLoadOther() 
{
	CFileDialog dlg(TRUE, "prt", portals.fn, OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_LONGNAMES | OFN_FILEMUSTEXIST,
		"Portal files (*.prt)|*.prt|All Files (*.*)|*.*||", NULL);

	dlg.m_ofn.lpstrTitle = "Locate portal file";

	if(IDOK == dlg.DoModal())
	{
		_fullpath(portals.fn, dlg.GetPathName().GetBuffer(1), _MAX_PATH);
		m_fn_ctrl.SetWindowText(portals.fn);
	}
}