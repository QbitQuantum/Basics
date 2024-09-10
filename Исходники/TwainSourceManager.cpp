CTwainSourceManager::CTwainSourceManager(void)
	: State(EnumState::Prepare)
	, DSMModule(0)
	, DSMEntry(0)
	, WndNotify(0)
	, MessageLevelVAR(ERROR)
{
	// 初始化AppID
	AppID.Id = 0; 				// init to 0, but Source Manager will assign real value
	AppID.Version.MajorNum = 1;
	AppID.Version.MinorNum = 703;
	AppID.Version.Language = TWLG_USA;
	AppID.Version.Country  = TWCY_USA;
#ifdef WIN32
	lstrcpyA (AppID.Version.Info,  "TWAIN_32 Twacker 1.7.0.3  01/18/1999");
	lstrcpyA (AppID.ProductName,   "TWACKER_32");
#else
	lstrcpyA (AppID.Version.Info,  "TWAIN Twacker 1.7.0.3  01/18/1999");
	lstrcpyA (AppID.ProductName,   "TWACKER_16");
#endif

	AppID.ProtocolMajor = 1;//TWON_PROTOCOLMAJOR;
	AppID.ProtocolMinor = 7;//TWON_PROTOCOLMINOR;
	AppID.SupportedGroups =  DG_IMAGE | DG_CONTROL;
	lstrcpyA (AppID.Manufacturer,  "TWAIN Working Group");
	lstrcpyA (AppID.ProductFamily, "TWAIN Toolkit");

	// 注册响应窗口类
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));

	wc.hInstance = ::GetModuleHandleA(NULL);
	wc.lpfnWndProc = WndNotifyProc;
	wc.lpszClassName = NOTIFYWNDCLASSNAME;

	if(RegisterClass(&wc))
	{
		throw E_FAIL;
	}
}