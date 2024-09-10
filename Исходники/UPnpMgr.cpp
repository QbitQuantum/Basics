void CUPnpMgr::WriteAddedMappingToFile(void)
{
	CSingleLock		localLock(&m_cs, TRUE);

	CString		strDatFile;
	strDatFile.Format(_T("%sUPnp.dat"), thePrefs.GetMuleDirectory(EMULE_CONFIGDIR));

	CFile		file;
	if (!file.Open(strDatFile, CFile::modeCreate | CFile::modeReadWrite))
		return;

	try
	{
		CArchive	ar(&file, CArchive::store);

		int						iCount;

		iCount = m_setAddedMapping.size();
		ar << iCount;

		set<CUPnpNatMappingKey>::iterator	it;
		for (it = m_setAddedMapping.begin(); it != m_setAddedMapping.end(); it++)
		{
			//it->Serialize(ar);
			CUPnpNatMappingKey      key(*it);  
			key.Serialize(ar); 
		}
		ar.Close();
	}
	catch (CArchiveException *e)
	{
		e->Delete();
		e = NULL;
	}

	file.Close();
}