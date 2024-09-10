CRotateDispWnd::CRotateDispWnd(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CRotateDispWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	msg_tray=RegisterWindowMessage("WM_APP_WM_USER_TRAY_RotateDisp");
	msg_bar=RegisterWindowMessage("TaskbarCreated");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hDlgWnd=NULL;
	ImmDisableIME(-1);
	
	IsAboutDlgShow=false;
	IsMouseDllOk=false;
	if(PathFileExists("RotateMouse.dll"))
		IsMouseDllOk=true;
}