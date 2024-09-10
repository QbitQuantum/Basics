MetroWindow::MetroWindow() :m_pDirect2dFactory(NULL),
m_pRenderTarget(NULL),
m_pMinButtonActiveBrush(NULL),
m_pMetroButtonNsBrush(NULL),
m_pMetroButtonLsBrush(NULL),
m_EdgeViewBrush(NULL),
m_pLightWhiteBrush(NULL),
m_pControlTextBrush(NULL),
m_pDWriteTypography(NULL),
m_pCloseButtonClickBrush(NULL),
m_pWICFactory(NULL),
m_pBitmap(NULL),
m_pBitmapBkg(NULL),
m_pITextFormatTitle(NULL),
m_pITextFormatContent(NULL),
m_pIDWriteFactory(NULL),
IsInvalid(false),
_bMouseTrack(TRUE),
iseThreadID(0),
dwExit(0)
{
	if (IsUserAnAdmin())
	{
		windowTitle = L"Metro USB Drives Boot Manager [";
		windowTitle += MUI::muiController.atString(L"Adm", L"Administrator") + L"]";
	}
	else{
		windowTitle = L"Metro USB Drives Boot Manager";
	}
	Notes =MUI::muiController.atString(L"NoticeInfo", DEFAULT_NOTES);
	if (localeinfo.lcid == 2052)
	{
		FontTabel = 1;
	}
	else{
		FontTabel = 0;
	}
	MTNotices = L"Notices Center:";
	JobStatusRate = L"Task not start";
	ProcessInfo = L"Manager Task Rate:";
	copyright = L"Copyright \xA9 2015 Force Charlie.";
	m_mbFind.bStatus = false;
	m_mbFind.caption =MUI::muiController.atString(L"Discover",L"Discover...");
	m_FixBoot.bStatus = false;
	m_FixBoot.caption = MUI::muiController.atString(L"Fixboot", L"Fix Boot");
	m_Operate.bStatus = false;
	//m_Operate.caption =muiController->m_langmap[L"BMake"];
	m_Operate.caption = MUI::muiController.atString(L"BMake",L"Expand Image");
	USBdrive = MUI::muiController.atString(L"USBdrive", L"USB Drives:");
	ImageFile = MUI::muiController.atString(L"ImageFile", L"Image File:");
	ImageSize = MUI::muiController.atString(L"ImageSize", L"Image Size:");
	Description = MUI::muiController.atString(L"Description", L"Description:");

	normalFont = MUI::muiController.atString(L"NormalFont", L"Segoe UI");
	
}