int CContactDlg::phoneTypeToInt( LPCWSTR val )
{
	for(int i=0; g_phoneTypes[i]; i++)
	{
		if(!StrCmpI(val, g_phoneTypes[i]))
		{
			return i;
		}
	}
	return 0;
}