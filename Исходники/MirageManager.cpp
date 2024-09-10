void CMirageManager::WriteDiagnostics(const std::wstring& data)
{
	std::wstring sFileName(_wgetenv(_T("APPDATA")));
	sFileName.append(_T("\\Dimdim\\DriverDiagnostics.info"));
	FILE* fout = _wfopen(sFileName.c_str(), _T("a+"));
	fwprintf(fout, _T("%s\n"), data.c_str());
	fclose(fout);
}