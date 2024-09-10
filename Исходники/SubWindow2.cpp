SubWindow2::SubWindow2(HWND hwnd,int x,int y)
{	
	HMODULE hModule = ::GetModuleHandle(0);
	applicationpath  = (wchar_t*)malloc((MAX_PATH+1)*sizeof(wchar_t)); 
	GetModuleFileName(NULL, applicationpath, MAX_PATH);
	(wcsrchr(applicationpath, '\\'))[1] = 0;
	int ww = 700,wh=500;
	OleInitialize(0);
	ltskinview= CreateLTFrameInstance(this,L"LTFrame",hwnd,WS_POPUP | WS_VISIBLE,x,y,ww,wh,0);
	SubWindowC =this;
	ltskinview->BindUserFunction("DragWindow",DragWindowFun2,0);
	//ltskinview->BindUserFunction("CloseWindow",CloseWindowFun,0);
	//ltskinview->BindUserFunction("MinWindow",MinWindowFun,0);
	SetWindowText(ltskinview->windowHandle(),L"LTFrame");
	wstring path = wstring(applicationpath)+L"./template/SubWindow.html";
	ltskinview->loadFile(path.c_str());
	ltskinview->EnableDragFrameChangeSize(false);
	SetForegroundWindow(ltskinview->windowHandle());
	//ltskinview->MessageLoop();
}