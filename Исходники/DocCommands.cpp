bool CDocCommands::DoCommand(LPCTSTR rstrCommand, LPCTSTR strValue)
{
	CString strCommand = rstrCommand;
	strCommand.MakeUpper();
	CString strSubCommand = strValue;
	strSubCommand.MakeUpper();
	int iValue = _ttoi(strValue);

	if (!m_DocWindow.m_hWnd)
		return (strCommand == "CLOSE" ? true : false);

	bool bOK = false;
	// Commands from the main dialog
	     if (strCommand == "STARTOVER")
		bOK = StartOver();
	else if (strCommand == "ZOOMIN")
		bOK = ZoomIn();
	else if (strCommand == "ZOOMOUT")
		bOK = ZoomOut();
	else if (strCommand == "ZOOMFULL")
		bOK = ZoomFull();

	// Commands from the File Operations tab
	else if (strCommand == "FILETAB")
		bOK = FileTab(strSubCommand);

	// Commands from the Crop tab
	else if (strCommand == "CROPTAB")
		bOK = CropTab(iValue);

	// Commands from the Resize tab
	else if (strCommand == "RESIZETAB")
		bOK = ResizeTab(iValue, NULL);
	else if (strCommand == "RESIZEAPPLY")
		bOK = ResizeTab(EDIT_APPLY, strValue);

	// Commands from the Flip & Rotate tab
	else if (strCommand == "FLIPROTATETAB")
		bOK = FlipRotateTab(iValue);
	else if (strCommand == "FLIPROTATETABSUBCOMMAND")
		bOK = FlipRotateTabSubCommand(strSubCommand);

	// Commands from the Recolor Area Fill tab
	else if (strCommand == "RECOLORTAB")
		bOK = RecolorTab(iValue);
	else if (strCommand == "RECOLORTABSUBCOMMAND")
		bOK = RecolorTabSubCommand(strSubCommand);

	else if (strCommand == "SETPRIMARYCOLOR")
		m_DocWindow.m_ToolSettings.m_PrimaryColor = iValue;
	else if (strCommand == "SETSECONDARYCOLOR")
		m_DocWindow.m_ToolSettings.m_SecondaryColor = iValue;
	else if (strCommand == "TOLERANCE")
		m_DocWindow.m_ToolSettings.m_nTolerance = iValue;

	// Commands from the Special Effects tab
	else if (strCommand == "EFFECTSTAB")
		bOK = EffectsTab(iValue);
	else if (strCommand == "EFFECTSTABSUBCOMMAND")
		bOK = EffectsTabSubCommand(strSubCommand);

	// Commands from the Contrast & Brightness tab
	else if (strCommand == "CONTRASTBRIGHTNESSTAB")
		bOK = ContrastBrightnessTab(iValue);
	else if (strCommand == "AUTOCORRECT")
		bOK = AutoCorrect();

	// Commands from the Hue & Saturation tab
	else if (strCommand == "COLORSTAB")
		bOK = ColorsTab(iValue);
	else if (strCommand == "MAKEGRAY")
		bOK = MakeGray();
	else if (strCommand == "INVERT")
		return Invert();

	// Commands from the Red Eye Removal tab
	else if (strCommand == "REDEYETAB")
		bOK = RedEyeTab(iValue);

	// Commands from the Frames & Borders tab
	else if (strCommand == "BORDERSTAB")
		bOK = BordersTab(iValue);
	else if (strCommand == "BORDERIMAGE")
		bOK = BorderImageMerge(strValue);
	else if (strCommand == "BORDERTYPE")
		bOK = BorderType(strValue);
	else if (strCommand == "BORDERSIZE")
		bOK = BorderSize(iValue);
	else if (strCommand == "BORDERSOFTNESS")
		bOK = SetBorderSoftness(iValue);
	else if (strCommand == "BORDERSTRETCH")
		bOK = SetBorderStretch(!!iValue);
	else
		CMessageBox::Message(String("'%s' is not implemented.", strCommand));

	return bOK;
}