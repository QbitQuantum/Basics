BOOL COXCsvFile::GetColumns(int nNumExpected)
{
	m_arrColumns.RemoveAll();
	m_arrColumns.SetSize(nNumExpected);
	m_nColumns=nNumExpected;
	
	if(ReadLine() || GetLastError()==errTooManyColumns)
	{
		if(m_nColumns<m_arrColumns.GetSize())
			m_nColumns= PtrToInt(m_arrColumns.GetSize());

		for(int nColumn=0; nColumn<m_nColumns; ++nColumn)
		{
			m_arrColumns[nColumn].m_sName=m_arrColumns[nColumn].m_strData;
			m_arrColumns[nColumn].m_strData.Empty();
		}
		return m_nColumns==nNumExpected;
	}

	return FALSE;
}