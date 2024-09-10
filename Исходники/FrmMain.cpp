//--------------------------------------------------------------------------------------------------------------//
void CFrmMain::WindowPlacementLoad()
{
	WINDOWPLACEMENT wndpl;

	CXMLParamsHelper XMLParams;
	XMLParams.LoadXMLParams();

	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("MaxPositionX"), &wndpl.ptMaxPosition.x, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("MaxPositionY"), &wndpl.ptMaxPosition.y, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("MinPositionX"), &wndpl.ptMinPosition.x, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("MinPositionY"), &wndpl.ptMinPosition.y, 0xffff);

	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("NormalPositionLeft"), &wndpl.rcNormalPosition.left, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("NormalPositionTop"), &wndpl.rcNormalPosition.top, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("NormalPositionRight"), &wndpl.rcNormalPosition.right, 0xffff);
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("NormalPositionBottom"), &wndpl.rcNormalPosition.bottom, 0xffff);

	long nVal = 0xffff;
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("Flags"), &nVal, 0xffff);
	wndpl.flags = nVal;
	XMLParams.GetXMLLong(SETTINGS_WINDOW_PLACEMENT_KEY, _T("ShowCmd"), &nVal, 0xffff);
	wndpl.showCmd = nVal;

	if(0xffff == wndpl.rcNormalPosition.left
		|| 0xffff == wndpl.rcNormalPosition.top || 0xffff == wndpl.rcNormalPosition.right
		|| 0xffff == wndpl.rcNormalPosition.bottom || 0xffff == wndpl.showCmd)
	{
		return;
	}

	SetWindowPlacement(&wndpl);
}