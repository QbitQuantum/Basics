BuildTag::BuildTag(const wxString &str)
{
	wxArrayString strings = wxStringTokenize(str, _T("-"));
	if (strings.GetCount() >= 3)
	{
		m_buildType = strings[0];
		m_jobName = strings[1];
		m_buildNumber = atoi(TOASCII(strings[strings.GetCount() - 1]));
	}
	else
	{
		m_buildType = _T("CustomBuild");
		m_jobName = _T("MultiMC");
		m_buildNumber = 0;
	}
}