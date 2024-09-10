void KviInputHistory::save(const QString & szFileName)
{
	KviConfigurationFile c(szFileName, KviConfigurationFile::Write);
	c.clear();

	c.writeEntry("Count", static_cast<unsigned>(m_StringList.size()));

	KviCString szTmp;
	int iIdx = 0;

	for(auto & szString : m_StringList)
	{
		if(!szString.isEmpty())
		{
			szTmp.sprintf("S%d", iIdx);
			c.writeEntry(szTmp.ptr(), szString);
			iIdx++;
		}
	}
}