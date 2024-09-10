bool CStarNetServerIrcDDBSet::Validate()
{
	bool res = getHostname().IsEmpty();
	if (res) {
		wxMessageDialog dialog(this, _("The Hostname may not be empty"), m_title + _(" Error"), wxICON_ERROR);
		dialog.ShowModal();
		return false;
	}

	res = getUsername().IsEmpty();
	if (res) {
		wxMessageDialog dialog(this, _("The Username may not be empty"), m_title + _(" Error"), wxICON_ERROR);
		dialog.ShowModal();
		return false;
	}

	return true;
}