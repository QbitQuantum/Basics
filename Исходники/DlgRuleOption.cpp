//重画函数
VOID CDlgRuleOption::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CDC DCBuffer;
	CBitmap ImageBuffer;
	DCBuffer.CreateCompatibleDC(&dc);
	DCBuffer.SetTextAlign(TA_LEFT|TA_TOP);
	ImageBuffer.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	//设置 DC
	DCBuffer.SetBkMode(TRANSPARENT);
	DCBuffer.SelectObject(&ImageBuffer);
	DCBuffer.SelectObject(CSkinResourceManager::GetDefaultFont());

	//绘画背景
	CImageHandle HandleViewBack(&m_ImageViewBack);
	m_ImageViewBack.BitBlt(DCBuffer,0,0);

	//绘画信息
	if (m_bControl==false)
	{
		//设置 DC
		DCBuffer.SetTextColor(RGB(64,10,10));

		//游戏模式
		TCHAR szModeString[64]=TEXT("");
		LPCTSTR pszGameMode[]={TEXT("快棋模式"),TEXT("慢棋模式"),TEXT("自定义模式")};
		_sntprintf(szModeString,CountChar(szModeString),TEXT("游戏模式：%s"),pszGameMode[m_GameRuleInfo.cbCurrentMode-1]);

		//游戏局时
		TCHAR szDrawString[64]=TEXT("");
		_sntprintf(szDrawString,CountChar(szDrawString),TEXT("游戏局时：%d 分钟"),m_GameRuleInfo.wRuleDrawTime/60);

		//游戏步时
		TCHAR szStepString[64]=TEXT("");
		_sntprintf(szStepString,CountChar(szStepString),TEXT("游戏步时：%d 分钟"),m_GameRuleInfo.wRuleStepTime/60);

		//游戏读秒
		TCHAR szSecondString[64]=TEXT("");
		_sntprintf(szSecondString,CountChar(szSecondString),TEXT("读秒时间：%d 秒"),m_GameRuleInfo.wRuleSecondTime);

		//输出信息
		const INT nXPos=50,nYPos=87,nStringSpace=25;
		DCBuffer.TextOut(nXPos,nYPos,szModeString,lstrlen(szModeString));
		DCBuffer.TextOut(nXPos,nYPos+nStringSpace,szDrawString,lstrlen(szDrawString));
		DCBuffer.TextOut(nXPos,nYPos+nStringSpace*2,szStepString,lstrlen(szStepString));
		DCBuffer.TextOut(nXPos,nYPos+nStringSpace*3,szSecondString,lstrlen(szSecondString));
	}

	//设置 DC
	DCBuffer.SetTextColor(RGB(125,125,125));
	DCBuffer.SetTextAlign(TA_CENTER|TA_TOP);

	//剩余时间
	TCHAR szTimeLeave[32]=TEXT("");
	_sntprintf(szTimeLeave,CountChar(szTimeLeave),TEXT("此对话框在 %d 秒后自动关闭"),m_nResidualTime);
	DCBuffer.TextOut(rcClient.Width()/2,rcClient.bottom-80,szTimeLeave,lstrlen(szTimeLeave));

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&DCBuffer,0,0,SRCCOPY);

	//清理资源
	DCBuffer.DeleteDC();
	ImageBuffer.DeleteObject();

	return;
}