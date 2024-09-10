	BOOL GetTextExtentPoint32W_AnyBuild(
		HDC		hdc, 
		LPCWSTR	lpString, 
		int		cbString, 
		LPSIZE	lpSize
	)
	{
		vector<char> buf;
		wcstombs_vector(lpString,cbString,&buf);
		return GetTextExtentPoint32A(
			hdc,
			&buf[0],
			buf.size()-1,
			lpSize
		);
	}