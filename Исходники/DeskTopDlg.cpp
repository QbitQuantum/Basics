HICON GetFileIcon(LPCWSTR pszFilePath)
{
	SHFILEINFOW sfi = {0};
	SHGetFileInfo(pszFilePath, -1, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX);

	// Retrieve the system image list.
	// To get the 48x48 icons, use SHIL_EXTRALARGE
	// To get the 256x256 icons (Vista only), use SHIL_JUMBO
	HIMAGELIST* imageList;
	HRESULT hResult = SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void**)&imageList);
	HICON hIcon;
	if (hResult == S_OK) {
		// Get the icon we need from the list. Note that the HIMAGELIST we retrieved
		// earlier needs to be casted to the IImageList interface before use.
		
		hResult = ((IImageList*)imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);

		if (hResult == S_OK) {

		}
	}

	return hIcon;
}