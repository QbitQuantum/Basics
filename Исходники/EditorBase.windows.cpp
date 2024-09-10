bool EditorBase::SaveForm(
	const FILE_FORM_FILTER& filter,
	const char *szDir,
	char *szoFilePathName,
	char *szoFileName)
{
	char fileInfo[___OUTPUT_LENGTH] = "\0";
	char fileName[___OUTPUT_LENGTH];

	std::string sInitDir = Platform::AddLastSlash(szDir), out;

	OPENFILENAMEA saveFileName;
	saveFileName.lStructSize       = sizeof(saveFileName);
	saveFileName.hwndOwner         = NULL;
	saveFileName.hInstance         = 0;
	saveFileName.lpstrFilter       = AssembleWin32FilterString(filter, out);
	saveFileName.lpstrCustomFilter = NULL;
	saveFileName.nMaxCustFilter    = 0;
	saveFileName.nFilterIndex      = 1;
	saveFileName.lpstrFile         = fileInfo;
	saveFileName.nMaxFile          = ___OUTPUT_LENGTH;
	saveFileName.lpstrFileTitle    = fileName;
	saveFileName.nMaxFileTitle     = ___OUTPUT_LENGTH;
	saveFileName.lpstrInitialDir   = sInitDir.c_str();
	saveFileName.lpstrTitle        = NULL;
	saveFileName.Flags             = (OFN_OVERWRITEPROMPT);
	saveFileName.lpstrDefExt       = NULL;

	if (!GetSaveFileNameA(&saveFileName))
	{
		return false;
	}

	_ETH_SAFE_strcpy(szoFileName, fileName);
	_ETH_SAFE_strcpy(szoFilePathName, fileInfo);
	return true;
}