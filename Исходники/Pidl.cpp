IShellFolder* sh_get_folder_interface(LPCITEMIDLIST pIDFolder)
{
	IShellFolder* pShellFolder = NULL;
	IShellFolder* pThisFolder  = NULL;
	HRESULT hr;

	hr = SHGetDesktopFolder(&pShellFolder);
	if (NOERROR != hr)
		return NULL;

	if (NextID(pIDFolder) == pIDFolder)
		return pShellFolder;

	hr = pShellFolder->BindToObject(
		pIDFolder, NULL, IID_IShellFolder, (LPVOID*)&pThisFolder);

	pShellFolder->Release();

	if (NOERROR != hr)
		return NULL;

	return pThisFolder;
}