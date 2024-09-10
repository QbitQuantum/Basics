wstring Win32CallstackResolver::pdbBrowse(wstring startingPoint)
{
	OPENFILENAMEW ofn;
	RDCEraseMem(&ofn, sizeof(ofn));

	wchar_t outBuf[MAX_PATH*2];
	wcscpy_s(outBuf, startingPoint.c_str());

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrTitle = L"Locate PDB File";
	ofn.lpstrFilter = L"PDB File\0*.pdb\0";
	ofn.lpstrFile = outBuf;
	ofn.nMaxFile = MAX_PATH*2-1;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST; // | OFN_ENABLEINCLUDENOTIFY | OFN_ENABLEHOOK

	BOOL ret = GetOpenFileNameW(&ofn);

	if(ret == FALSE)
		return L"";

	return outBuf;
}