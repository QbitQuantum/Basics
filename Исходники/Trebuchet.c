int TrebuchetFormBuilder()
{
	char buffer[32];

	int nPadding; // Padding between elements
	int nRangeY, nRangeWidth, nRangeHeight, nRangeStaticY, nRangeStaticWidth; // Range edit and static
	int nRechargeY, nRechargeWidth, nRechargeHeight, nRechargeStaticX, nRechargeStaticY, nRechargeStaticWidth;
	int nMinX, nSMinX; // Minimum range edit box
	int nMaxX, nSMaxX; // Maximum range edit box
	int nTSCBx, nTSCBy, nTSCBwidth, nTSCBheight; // Scrollbar position
	int nTVRx, nTVRy, nTVRwidth, nTVRheight; // Value static position
	int nTSBx, nTSBwidth, nTSBheight; // Start button position
	int nTDBx, nTDBy, nTDBwidth, nTDBheight; // Duration static position

	nPadding = 20;

	nRangeY = DEFBUT_HEIGHT + nPadding;
	nRangeWidth = nPadding * 2;
	nRangeHeight = TAB_CHAT_HEIGHT ? TAB_CHAT_HEIGHT : TAB_STATIC_HEIGHT;
	nRangeStaticY = nRangeY + 2;
	nRangeStaticWidth = 60;

	nMinX = nPadding;
	nSMinX = nMinX + nRangeWidth + 5;

	nMaxX = nSMinX + nRangeStaticWidth + nPadding;
	nSMaxX = nMaxX + nRangeWidth + 5;

	// Scroll Bar position
	nTSCBx = nPadding;
	nTSCBy = (int)(nPadding / 2) + nRangeY + nRangeHeight;
	nTSCBwidth = UserSettings.ClientWidth - (nPadding * 7);
	nTSCBheight = (nPadding / 2);

	// Recharge Edit
	nRechargeY = (nPadding / 2) + nTSCBy + nTSCBheight;
	nRechargeWidth = nPadding *2;
	nRechargeHeight = TAB_CHAT_HEIGHT ? TAB_CHAT_HEIGHT : TAB_STATIC_HEIGHT;
	nRechargeStaticX = nPadding + nRechargeWidth + 5;
	nRechargeStaticY = nRechargeY + 2;
	nRechargeStaticWidth = 60;

	// Value Readout position
	nTVRx = nTSCBx + nTSCBwidth + (nPadding / 2);
	nTVRy = nTSCBy;
	nTVRwidth = nPadding * 5;
	nTVRheight = nPadding;

	// Start button position
	nTSBwidth = DEFBUT_WIDTH;
	nTSBheight = DEFBUT_HEIGHT;
	nTSBx = (UserSettings.ClientWidth - nPadding) - DEFBUT_WIDTH;
	g_nSBy = (UserSettings.ClientHeight - nPadding) - DEFBUT_HEIGHT - TAB_CHAT_HEIGHT;

	// Duration timer position
	nTDBx = nPadding;
	nTDBy = (UserSettings.ClientHeight - nPadding) - abs(nPadding / 2) - TAB_CHAT_HEIGHT;
	nTDBwidth = UserSettings.ClientWidth - (nPadding * 2) - DEFBUT_WIDTH;
	nTDBheight = nPadding;

	// Minimum range edit box
	memset(buffer, 0, sizeof(buffer));
	_snprintf(buffer, sizeof(buffer)-1, "%lu", UserSettings.TrebMin);
	GlobalSettings.hTrebMinEdit = CreateWindow(
		TEXT("edit"), NULL,
		WS_CHILDWINDOW | WS_VISIBLE | ES_RIGHT | WS_BORDER | ES_AUTOHSCROLL,
		nMinX, nRangeY, nRangeWidth, nRangeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	hMinStatic = CreateWindow(
		TEXT("static"), "Minimum",
		WS_CHILD | SS_EDITCONTROL,
		nSMinX, nRangeStaticY, nRangeStaticWidth, nRangeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SendMessage(GlobalSettings.hTrebMinEdit, EM_SETLIMITTEXT, (WPARAM)MAXRNG, 0);
	SendMessage(GlobalSettings.hTrebMinEdit, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);
	SendMessage(GlobalSettings.hTrebMinEdit, WM_SETTEXT, 0, (LPARAM)buffer);
	SendMessage(hMinStatic, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);

	// Maximum range edit box
	memset(buffer, 0, sizeof(buffer));
	_snprintf(buffer, sizeof(buffer)-1, "%lu", UserSettings.TrebMax);
	GlobalSettings.hTrebMaxEdit = CreateWindow(
		TEXT("edit"), NULL,
		WS_CHILDWINDOW | ES_RIGHT | WS_BORDER | ES_AUTOHSCROLL,
		nMaxX, nRangeY, nRangeWidth, nRangeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	hMaxStatic = CreateWindow(
		TEXT("static"), "Maximum",
		WS_CHILD | SS_EDITCONTROL,
		nSMaxX, nRangeStaticY, nRangeStaticWidth, nRangeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SendMessage(GlobalSettings.hTrebMaxEdit, EM_SETLIMITTEXT, (WPARAM)MAXRNG, 0);
	SendMessage(GlobalSettings.hTrebMaxEdit, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);
	SendMessage(GlobalSettings.hTrebMaxEdit, WM_SETTEXT, 0, (LPARAM)buffer);
	SendMessage(hMaxStatic, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);

	// Scroll bar
	GlobalSettings.hTrebSliderBar = CreateWindow(
		TEXT("scrollbar"), NULL,
		WS_CHILD | WS_VISIBLE | SBS_HORZ,
		nTSCBx, nTSCBy, nTSCBwidth, nTSCBheight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SetScrollRange(GlobalSettings.hTrebSliderBar, SB_CTL, UserSettings.TrebMin, UserSettings.TrebMax, FALSE);
	SetScrollPos(GlobalSettings.hTrebSliderBar, SB_CTL, UserSettings.TrebRange, FALSE);

	// Value readout
	GlobalSettings.hTrebSliderValue = CreateWindow(
		TEXT("static"), "Range: 0.00",
		WS_CHILD | WS_VISIBLE | SS_EDITCONTROL,
		nTVRx, nTVRy, nTVRwidth, nTVRheight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	memset(buffer, 0, sizeof(buffer));
	_snprintf(buffer, sizeof(buffer)-1, "Range: %.2f", (((float)(UserSettings.TrebRange - UserSettings.TrebMin) / (float)(UserSettings.TrebMax - UserSettings.TrebMin)) * 100) );
	SendMessage(GlobalSettings.hTrebSliderValue, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);
	SendMessage(GlobalSettings.hTrebSliderValue, WM_SETTEXT, 0, (LPARAM)buffer);

	// Recharge edit box
	memset(buffer, 0, sizeof(buffer));
	_snprintf(buffer, sizeof(buffer)-1, "%lu", UserSettings.TrebRecharge);
	GlobalSettings.hTrebRecharge = CreateWindow(
		TEXT("edit"), NULL,
		WS_CHILDWINDOW | ES_RIGHT | WS_BORDER | ES_AUTOHSCROLL,
		nPadding, nRechargeY, nRechargeWidth, nRechargeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	hRechargeStatic = CreateWindow(
		TEXT("static"), "Recharge",
		WS_CHILD | SS_EDITCONTROL,
		nRechargeStaticX, nRechargeStaticY, nRechargeStaticWidth, nRangeHeight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SendMessage(GlobalSettings.hTrebRecharge, EM_SETLIMITTEXT, (WPARAM)MAXRNG, 0);
	SendMessage(GlobalSettings.hTrebRecharge, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);
	SendMessage(GlobalSettings.hTrebRecharge, WM_SETTEXT, 0, (LPARAM)buffer);
	SendMessage(hRechargeStatic, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);

	// Start button
	GlobalSettings.hTrebStartButton = CreateWindow(
		TEXT("button"), "Start",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		nTSBx, g_nSBy, nTSBwidth, nTSBheight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SendMessage(GlobalSettings.hTrebStartButton, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);

	// Duration box
	GlobalSettings.hTrebDurationBox = CreateWindow(
		TEXT("static"), "Runtime: 0.00s",
		WS_CHILD | WS_VISIBLE | SS_EDITCONTROL,
		nTDBx, nTDBy, nTDBwidth, nTDBheight,
		GlobalSettings.hMainWindow, NULL, GlobalSettings.hInstance, NULL);
	SendMessage(GlobalSettings.hTrebDurationBox, WM_SETFONT, (WPARAM)GlobalSettings.hFont, 0);

	return 1;
}