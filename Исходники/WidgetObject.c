BOOL
OxWidget_ReleaseChildren(OxWidgetObject* ox)
{
	if (ox->hWin)
		EnumChildWindows(ox->hWin, OxWidgetReleaseEnumProc, 0);
	return TRUE;
}