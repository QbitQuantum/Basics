//绘画背景
BOOL CServerItmOpaint::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),24);

	//创建 DC
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(pDC);
	BufferDC.SelectObject(ImageBuffer);

	//加载资源
	CImageHandle HandleTitleL(&m_ImageTitleL);
	CImageHandle HandleTitleM(&m_ImageTitleM);
	CImageHandle HandleTitleR(&m_ImageTitleR);

	//绘画背景
	//m_ImageTitleL.BitBlt(BufferDC,0,0);

	//填充中间
	for (INT nXPos=0;nXPos<rcClient.Height()-m_ImageTitleR.GetHeight();nXPos+=m_ImageTitleM.GetHeight())
	{
		m_ImageTitleM.BitBlt(BufferDC,0,nXPos);
	}
	//绘画背景
	m_ImageTitleR.BitBlt(BufferDC,0,rcClient.Height()-m_ImageTitleR.GetHeight());
    
	//设置 DC
	BufferDC.SetTextColor(CR_TEXT);
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(CSkinResourceManager::GetDefaultFont());

	//用户信息
	if (m_bShowInfo==true)
	{
		//变量定义
		tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

		//用户头像
		g_GlobalUnits.m_UserFaceRes->DrawNormalFace(&BufferDC,10,12,GlobalUserInfo.cbGender,GlobalUserInfo.dwUserID,GlobalUserInfo.dwCustomFaceVer,32,32);

		//构造位置
		TCHAR szBuffer[255]=TEXT("");
		CRect rcAccounts(50,15,rcClient.Width()-20,27);
		CRect rcUnderWrite(50,32,rcClient.Width()-20,44);

		//用户帐号
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("用户帐号：%s [ %ld ]"),GlobalUserInfo.szAccounts,GlobalUserInfo.dwGameID);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcAccounts,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);

		//会员信息
		LPCTSTR pszMemberOrder[]={TEXT("非会员"),TEXT("红钻会员"),TEXT("蓝钻会员"),TEXT("黄钻会员"),TEXT("紫钻会员")};
		if (GlobalUserInfo.cbMember<CountArray(pszMemberOrder))
		{
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("会员等级：%s"),pszMemberOrder[GlobalUserInfo.cbMember]);
			BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcUnderWrite,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		}
	}
    //绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferDC.DeleteDC();
	ImageBuffer.Destroy();

	return TRUE;
}