/**
 * name:		DlgExIm_SaveFileName
 * desc:		displayes a slightly modified SaveFileName DialogBox
 * params:		hWndParent		- parent window
 *				pszTitle		- title for the dialog
 *				pszFilter		- the filters to offer
 *				pszFile			- this is the buffer to store the file to (size must be MAX_PATH)
 * return:		-1 on error/abort or filter index otherwise
 **/
int DlgExIm_SaveFileName(HWND hWndParent, LPCSTR pszTitle, LPCSTR pszFilter, LPSTR pszFile)
{
	OPENFILENAMEA ofn;
	CHAR szInitialDir[MAX_PATH];

	InitOpenFileNameStruct(&ofn, hWndParent, pszTitle, pszFilter, szInitialDir, pszFile);
	ofn.Flags |= OFN_OVERWRITEPROMPT;

	if (!GetSaveFileNameA(&ofn)) {
		DWORD dwError = CommDlgExtendedError();

		if (dwError) MsgErr(ofn.hwndOwner, LPGENT("The SaveFileDialog returned an error: %d!"), dwError);
		return -1;
	}
	SaveInitialDir(pszFile);
	return ofn.nFilterIndex;
}