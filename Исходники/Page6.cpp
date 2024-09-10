void CPage6::OnDestroy()
{
	if (m_ulChangeIconNotifyID != 0)
	{
		SHChangeNotifyDeregister(m_ulChangeIconNotifyID);
	}
	CMFCPropertyPage::OnDestroy();
}