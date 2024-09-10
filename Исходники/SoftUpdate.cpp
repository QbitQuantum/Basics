CString GetJsonValue(CString str,CString key)
{
	str.Remove('{');
	str.Remove('}');
	int index=0;
	CString resToken=str.Tokenize(_T(","),index);
	while (resToken != _T(""))
	{
		int index1=0;
		CString resToken1=resToken.Tokenize(_T(":"),index1);
		int flag=0;
		while(resToken1!=_T(""))
		{
			if (flag)
			{
				return resToken1;
			}
			if (resToken1==key)
			{
				flag=1; 
			}
			resToken1=resToken.Tokenize(_T(":"),index1);
		}
		resToken=str.Tokenize(_T(","),index);
	}
	return _T("");
}