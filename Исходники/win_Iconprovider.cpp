bool WinIconProvider::addIconFromImageList(int imageListIndex, int iconIndex, QIcon& icon) const
{
	HICON hIcon = 0;
	IImageList* imageList;
	HRESULT hResult = SHGetImageList(imageListIndex, IID_IImageList, (void**)&imageList);
	if (hResult == S_OK)
	{
		hResult = ((IImageList*)imageList)->GetIcon(iconIndex, ILD_TRANSPARENT, &hIcon);
		imageList->Release();
	}
	if (hResult == S_OK && hIcon)
	{
        icon.addPixmap(QtWin::fromHICON(hIcon));
		DestroyIcon(hIcon);
	}

	return SUCCEEDED(hResult);
}