int
ODBCStringsMatrix::CutToSmallStrings(char* szString, CStringArray& arrSmallStrings)
	{
	int nLoop	= 0;
	int	nStart	= 0;
	arrSmallStrings.RemoveAll();

	while( szString[nLoop] != '\0' )
		{
		if( szString[nLoop] == ' ' )
			{
			char	cOld	= szString[nLoop];
			szString[nLoop]	= '\0';
			CString sValue	= (LPCTSTR)&szString[nStart];
			szString[nLoop]	= cOld;

			if( sValue.GetLength() )
				arrSmallStrings.Add(sValue);
			nStart			= nLoop + 1;
			}

		nLoop ++;
		}

	CString sValue	= (LPCTSTR)&szString[nStart];
	sValue.Remove(' ');
	if( sValue.GetLength() )
		arrSmallStrings.Add(sValue);

	return (long)arrSmallStrings.GetCount();
	}