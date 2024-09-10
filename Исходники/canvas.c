/*
	ANT_CANVAS::LOAD_FILE()
	-----------------------
*/
long long ANT_canvas::load_file(void)
{
long long lines;
IFileDialog *pfd = NULL;
IShellItem *psiResult;
DWORD dwFlags;
PWSTR pszFilePath = NULL;
char chosen_filter[1024];
char chosen_filename[MAX_PATH];
OPENFILENAME parameters;

/*
	Create the Open Dialg object IFileDialog
*/
if ((CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)) == S_OK))
	{
	/*
		we're on VISTA / Windows 7 or later
	*/
	const COMDLG_FILTERSPEC c_rgSaveTypes[] =
	{
	{L"C/C++ files",		L"*.c;*.cxx;*.cpp;*.h;*.hpp.*.hxx;*.mak;makefile"},
	{L"All Documents (*.*)",		L"*.*"}
	};

	pfd->GetOptions(&dwFlags);
	pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);					// we want to see a file
	pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
	pfd->SetFileTypeIndex(1);										// first item in the list is the default
	pfd->SetDefaultExtension(L"doc;docx");
	if (pfd->Show(NULL) == S_OK)
		{
		if (pfd->GetResult(&psiResult) == S_OK)						// get the result object if the user clicks "Open"
			{
			psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

			lines = file->read_file((char *)pszFilePath);

			CoTaskMemFree(pszFilePath);
			psiResult->Release();
			}
		}
	pfd->Release();

	return lines;
	}
else
	{
	/*
		we're on something prior to VISTA (NT through to XP) so use the old-style common control
	*/
	memset(chosen_filename, 0, sizeof(chosen_filename));

	parameters.lStructSize = sizeof(parameters);
	parameters.hwndOwner = window;
	parameters.hInstance = hInstance;
	parameters.lpstrFilter = L"C/C++ files\0*.c;*.cxx;*.cpp;*.h;*.hpp.*.hxx\0\0\0";
	parameters.lpstrCustomFilter = (LPWSTR)chosen_filter;
	parameters.nMaxCustFilter = sizeof(chosen_filter) - 1;
	parameters.nFilterIndex = 1;
	parameters.lpstrFile = (LPWSTR)chosen_filename;
	parameters.nMaxFile = sizeof(chosen_filename) - 1;
	parameters.lpstrFileTitle = NULL;
	parameters.nMaxFileTitle = 0;
	parameters.lpstrInitialDir = NULL;
	parameters.lpstrTitle = L"Open...";
	parameters.Flags = OFN_LONGNAMES;
	parameters.nFileOffset = 0;
	parameters.nFileExtension = 0;
	parameters.lpstrDefExt = NULL;
	parameters.lCustData = 0;
	parameters.lpfnHook = NULL;
	parameters.lpTemplateName = 0;
	#if (_WIN32_WINNT >= 0x0500)
		parameters.pvReserved = NULL;
		parameters.dwReserved = 0;
		parameters.FlagsEx = 0;
	#endif

	if ((GetOpenFileNameW(&parameters)) != 0)
		return file->read_file((char *)parameters.lpstrFile);
	}

return 0;
}