bool HotspotImpl_FolderIcon::SetIconClickMode()
{
	SHELLFLAGSTATE aSt = {0};
	SHGetSettings( &aSt, SSF_DOUBLECLICKINWEBVIEW);

	bool aDblClkOpensIcons = (aSt.fDoubleClickInWebView != 0);
	if (aDblClkOpensIcons != myDblClkOpensIcons)
	{
		myDblClkOpensIcons = aDblClkOpensIcons;
		return true;
	}
	else
		return false;
}