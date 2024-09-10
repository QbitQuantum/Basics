int CNewBookmarkDialog::Run(const wxString &local_path, const CServerPath &remote_path)
{
	if (!Load(m_parent, _T("ID_NEWBOOKMARK")))
		return wxID_CANCEL;

	XRCCTRL(*this, "ID_LOCALPATH", wxTextCtrl)->ChangeValue(local_path);
	if (!remote_path.empty())
		XRCCTRL(*this, "ID_REMOTEPATH", wxTextCtrl)->ChangeValue(remote_path.GetPath());

	if (!m_server)
		XRCCTRL(*this, "ID_TYPE_SITE", wxRadioButton)->Enable(false);

	return ShowModal();
}