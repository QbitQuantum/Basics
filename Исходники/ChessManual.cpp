//初始化函数
BOOL CChessManual::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("中国象棋棋谱："));

	//移动窗口
	CImageHandle ImageHandeBack(&m_ImageBack);
	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE);

	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建控件
	const CSize & BoradSize=m_ChessBorad.GetChessBoradSize();
	m_ChessBorad.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,10);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btOpen.SetButtonImage(IDB_MANUAL_BT_OPEN,hInstance,false);
	m_btReLoad.SetButtonImage(IDB_MANUAL_BT_RELOAD,hInstance,false);
	m_btFirst.SetButtonImage(IDB_MANUAL_BT_FIRST,hInstance,false);
	m_btBefore.SetButtonImage(IDB_MANUAL_BT_BEFORE,hInstance,false);
	m_btNext.SetButtonImage(IDB_MANUAL_BT_NEXT,hInstance,false);
	m_btLast.SetButtonImage(IDB_MANUAL_BT_LAST,hInstance,false);
	m_btCancel.SetButtonImage(IDB_MANUAL_BT_CLOSE,hInstance,false);

	//计算位置
	CRect rcButton;
	m_btOpen.GetWindowRect(&rcButton);
	int nXButtonSpace=(rcClient.Width()-rcButton.Width()*7)/8;
	int nYPos=rcClient.Height()-rcButton.Height()-30;

	//移动按钮
	HDWP hDwp=BeginDeferWindowPos(7);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;
	DeferWindowPos(hDwp,m_btOpen,NULL,nXButtonSpace,nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btReLoad,NULL,nXButtonSpace*2+rcButton.Width(),nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btFirst,NULL,nXButtonSpace*3+rcButton.Width()*2,nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btBefore,NULL,nXButtonSpace*4+rcButton.Width()*3,nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btNext,NULL,nXButtonSpace*5+rcButton.Width()*4,nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btLast,NULL,nXButtonSpace*6+rcButton.Width()*5,nYPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btCancel,NULL,nXButtonSpace*7+rcButton.Width()*6,nYPos,0,0,uFlags);
	EndDeferWindowPos(hDwp);

	//移动控件
	m_ChessBorad.MoveWindow(29,29,BoradSize.cx,BoradSize.cy);
	m_ManualList.MoveWindow(BoradSize.cx+37,32,rcClient.Width()-BoradSize.cx-66,BoradSize.cy-8);

	//更新棋谱
	OnReLoad();

	return TRUE;
}