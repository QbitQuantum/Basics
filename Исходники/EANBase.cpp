// explode packed sets of bar
CString CEANBase::Explode (int nDigit, char chSet)
{
	CString strPack = m_strEAN[nDigit];
	if (chSet == 'B')
	{
		_strrev (strPack.GetBuffer (-1));
		strPack.ReleaseBuffer ();
	}

	char chFirst = chSet == 'C' ? '1' : '0';
	CString strResult;

	for (int i = 0; i < strPack.GetLength (); i++)
	{
		for (int j = 0; j < strPack.GetAt (i) - '0'; j++)
			strResult += chFirst;
		chFirst = chFirst == '1' ? '0' : '1';
	}
	
	return strResult;
}