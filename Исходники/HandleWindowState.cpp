/* Sets a tabs icon. Normally, this icon
is the folders icon, however if the tab
is locked, the icon will be a lock. */
void Explorerplusplus::SetTabIcon(int iIndex,int iTabId,LPITEMIDLIST pidlDirectory)
{
	TCITEM			tcItem;
	SHFILEINFO		shfi;
	ICONINFO		IconInfo;
	int				iImage;
	int				iRemoveImage;

	/* If the tab is locked, use a lock icon. */
	if(m_TabInfo[iTabId].bAddressLocked || m_TabInfo[iTabId].bLocked)
	{
		iImage = TAB_ICON_LOCK_INDEX;
	}
	else
	{
		SHGetFileInfo((LPCTSTR)pidlDirectory,0,&shfi,sizeof(shfi),
			SHGFI_PIDL|SHGFI_ICON|SHGFI_SMALLICON);

		/* TODO: The proxy icon may also be the lock icon, if
		the tab is locked. */
		SetTabProxyIcon(iTabId,shfi.hIcon);

		GetIconInfo(shfi.hIcon,&IconInfo);
		iImage = ImageList_Add(TabCtrl_GetImageList(m_hTabCtrl),
			IconInfo.hbmColor,IconInfo.hbmMask);

		DeleteObject(IconInfo.hbmColor);
		DeleteObject(IconInfo.hbmMask);
		DestroyIcon(shfi.hIcon);
	}

	/* Get the index of the current image. This image
	will be removed after the new image is set. */
	tcItem.mask		= TCIF_IMAGE;
	TabCtrl_GetItem(m_hTabCtrl,iIndex,&tcItem);

	iRemoveImage = tcItem.iImage;

	/* Set the new image. */
	tcItem.mask		= TCIF_IMAGE;
	tcItem.iImage	= iImage;
	TabCtrl_SetItem(m_hTabCtrl,iIndex,&tcItem);

	if(iRemoveImage != TAB_ICON_LOCK_INDEX)
	{
		/* Remove the old image. */
		TabCtrl_RemoveImage(m_hTabCtrl,iRemoveImage);
	}
}