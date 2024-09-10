//调整控件
void CGameFrameControl::RectifyControl(int nWidth, int nHeight)
{
	//状态判断
	if (m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//变量定义
	const int nComminutePos=nHeight*3/7;
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(20);

	//广告区域
	DeferWindowPos(hDwp,m_BrowerAD,NULL,LIST_LEFT,7,nWidth-LIST_LEFT-LIST_RIGHT,115,uFlags);

	//列表区域
	DeferWindowPos(hDwp,m_UserListView,NULL,LIST_LEFT,LIST_TOP,nWidth-LIST_LEFT-LIST_RIGHT,nComminutePos-LIST_TOP-LIST_BOTTOM,uFlags);

	

	//聊天区域
	DeferWindowPos(hDwp,m_ChatMessage,NULL,CHAT_LEFT,nComminutePos+CHAT_TOP,nWidth-CHAT_RIGHT-CHAT_LEFT,
		nHeight-nComminutePos-CHAT_TOP-CHAT_BOTTOM,uFlags);

	//聊天区域
	CRect rcButton;
	m_btPhrase.GetWindowRect(&rcButton);
	CButton * pButtonArray[]={&m_btExpression,&m_btColorSet,&m_btCleanScreen};
	for (int i=0;i<CountArray(pButtonArray);i++)
	{
		DeferWindowPos(hDwp,pButtonArray[i]->m_hWnd,NULL,CHAT_LEFT+(rcButton.Width()+5)*i,nHeight-61,rcButton.Width(),rcButton.Height(),uFlags);
	}
	m_btSendChat.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btSendChat,NULL,nWidth-rcButton.Width()-8,nHeight-33,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_ChatObject,NULL,8,nHeight-33,70,200,uFlags);
	DeferWindowPos(hDwp,m_ChatInput,NULL,81,nHeight-33,nWidth-rcButton.Width()-93,19,uFlags);

	//功能按钮
	m_btSound.GetWindowRect(&rcButton);
	int nBeginPos=22,nEndPos=nWidth-17;
	int nButtonSpace=(nEndPos-nBeginPos-4*rcButton.Width())/3,nYPosButton=nComminutePos-rcButton.Height()-7;
	DeferWindowPos(hDwp,m_btSound,NULL,nBeginPos,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btLookOn,NULL,nBeginPos+nButtonSpace+rcButton.Width(),nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btGameRule,NULL,nBeginPos+nButtonSpace*2+rcButton.Width()*2,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btGameOption,NULL,nBeginPos+nButtonSpace*3+rcButton.Width()*3,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	return;
}