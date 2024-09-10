// routine to find what a shortcut is pointing at
int
get_target(char *target_fname, char *retPath)
{
    HRESULT hres;
    IShellLink *shell_link;
    IPersistFile *persist_file;
    int result = 0;
	WCHAR wsz[MAX_PATH];

    hres = OleInitialize(NULL);
	if (hres != S_FALSE && hres != S_OK)
		return (-1);

    // Get a pointer to the IShellLink interface
    hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			  &IID_IShellLink, (void **) &shell_link);

	if (!SUCCEEDED(hres)) {
		OleUninitialize();
		return (-1);
	}

    // Get a pointer to the IPersistFile interface
    hres = shell_link->lpVtbl->QueryInterface(shell_link, &IID_IPersistFile,
					    (void **) &persist_file);

	if (SUCCEEDED(hres)) {
		// Ensure that the string is Unicode
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR) target_fname, -1, wsz, MAX_PATH);

		// Load the shortcut
		hres = persist_file->lpVtbl->Load(persist_file, wsz, STGM_READ);

		if (SUCCEEDED(hres)) {
			// read stuff from the link object and print it to the screen
			shell_link->lpVtbl->GetPath(shell_link, retPath,
							 MAX_PATH, NULL, SLGP_RAWPATH);
		} else
			result = -1;

		// Release the pointer to the IPersistFile interface
		persist_file->lpVtbl->Release(persist_file);
	}

	OleUninitialize();
	return(result);
}