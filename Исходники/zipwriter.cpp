wxString GetZipFileName (const wxString & suOriginName, ubyte4 uiArchive)
{
	wchar_t extension[30];

	if (uiArchive < 100)
		wsprintf (extension, L"%.2d", uiArchive);
	else
		wsprintf (extension, L"%d", uiArchive);

	wxString sName = suOriginName;
	wchar_t fileName[MAX_PATH];
	
	_wsplitpath (sName.c_str (), NULL, NULL, fileName, NULL);
	sName = fileName;
	sName += _(".z");
	sName += extension;

	return sName;
}