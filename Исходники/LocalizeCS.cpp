static void WriteString( HANDLE csv, int id, const wchar_t *string, int len, CSettingsParser &parser, int subid=INT_MAX )
{
	DWORD q;
	wchar_t buf[256];
	int len2;
	if (subid!=INT_MAX)
		len2=Sprintf(buf,_countof(buf),L"%d/%d",id,subid&65535);
	else
		len2=Sprintf(buf,_countof(buf),L"%d",id);

	const wchar_t *comment=parser.FindSetting(buf);
	if (comment && _wcsicmp(comment,L"ignore")==0)
		return;

	WriteFile(csv,buf,len2*2,&q,NULL);
	WriteFile(csv,L"\t",2,&q,NULL);

	for (int i=0;i<len;i++)
	{
		WORD c=string[i];
		if (c=='\t')
			WriteFile(csv,L"\\t",4,&q,NULL);
		else if (c=='\r')
			WriteFile(csv,L"\\r",4,&q,NULL);
		else if (c=='\n')
			WriteFile(csv,L"\\n",4,&q,NULL);
		else if (c=='\\')
			WriteFile(csv,L"\\\\",4,&q,NULL);
		else
			WriteFile(csv,&c,2,&q,NULL);
	}

	WriteFile(csv,L"\t\t",4,&q,NULL);
	if (comment)
		WriteFile(csv,comment,Strlen(comment)*2,&q,NULL);
	WriteFile(csv,L"\r\n",4,&q,NULL);
}