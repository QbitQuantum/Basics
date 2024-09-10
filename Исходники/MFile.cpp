BOOL CMFile::WriteString(LPCTSTR str)
{
	int len = strlen(str)+1;
	if (len >300) len = 300;
	short l = len;
	FWrite(&l,sizeof(short));
	FWrite((LPSTR)str,l);
	return TRUE;
	
}