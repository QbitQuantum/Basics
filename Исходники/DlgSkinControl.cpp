//重画消息
VOID CDlgSkinControl::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//变量定义
	CDC * pDC=CDC::FromHandle(ImageBuffer.GetDC());
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//绘画背景
	pDC->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);
	pDC->Draw3dRect(&rcClient,CSkinEdit::m_SkinAttribute.m_crEnableBorad,CSkinEdit::m_SkinAttribute.m_crEnableBorad);

	//加载资源
	CPngImageSB ImageSkinItem;
	ImageSkinItem.LoadImage(AfxGetInstanceHandle(),TEXT("SKIN_ITEM"));

	//绘画子项
	for (WORD nXPos=0;nXPos<4;nXPos++)
	{
		for (WORD nYPos=0;nYPos<2;nYPos++)
		{
			//变量定义
			WORD wIndex=nYPos*4+nXPos;
			WORD wImageIndex=(m_wHoverItem==wIndex)?1:0;
			tagSkinRenderInfo & SkinRenderInfo=m_RenderInfoItem[wIndex];

			//绘画子项
			ImageSkinItem.DrawImage(pDC,nXPos*(m_SizeSkinItem.cx+ITEM_SPACE_CX)+ITEM_ORIGIN_X,
				nYPos*(m_SizeSkinItem.cy+ITEM_SPACE_CY)+ITEM_ORIGIN_Y,m_SizeSkinItem.cx,m_SizeSkinItem.cy,
				(nYPos*4+nXPos)*m_SizeSkinItem.cx,wImageIndex*m_SizeSkinItem.cy);

			//绘画边框
			if ((m_CurrentRenderInfo.wColorH==SkinRenderInfo.wColorH)&&(m_CurrentRenderInfo.dRectifyS==SkinRenderInfo.dRectifyS)
				&&(m_CurrentRenderInfo.dRectifyB==SkinRenderInfo.dRectifyB))
			{
				INT nXDrawPos=nXPos*(m_SizeSkinItem.cx+ITEM_SPACE_CX)+ITEM_ORIGIN_X-2;
				INT nYDrawPos=nYPos*(m_SizeSkinItem.cy+ITEM_SPACE_CY)+ITEM_ORIGIN_Y-2;
				pDC->Draw3dRect(nXDrawPos,nYDrawPos,m_SizeSkinItem.cx+4,m_SizeSkinItem.cy+4,RGB(0,0,0),RGB(0,0,0));
			}
		}
	}

	//加载资源
	CPngImageSB ImageSkinColor;
	CPngImageSB ImageSkinButton;
	ImageSkinColor.LoadImage(AfxGetInstanceHandle(),TEXT("SKIN_COLOR"));
	ImageSkinButton.LoadImage(AfxGetInstanceHandle(),TEXT("SKIN_BUTTON"));

	//绘画色条
	for (WORD nIndex=0;nIndex<3;nIndex++)
	{
		//绘画色条
		INT nXDrawPos=COLOR_ORIGIN_X;
		INT nYDrawPos=COLOR_ORIGIN_Y+(m_SizeColorItem.cy+COLOR_SPACE_CY)*nIndex;
		ImageSkinColor.DrawImage(pDC,nXDrawPos,nYDrawPos,m_SizeColorItem.cx,m_SizeColorItem.cy,0,m_SizeColorItem.cy*nIndex);

		//绘画滑块
		switch (nIndex)
		{
		case 0:		//色相
			{
				INT nXButtonPos=nXDrawPos+(m_SizeColorItem.cx-6)*m_CurrentRenderInfo.wColorH/(MAX_COLOR_H-MIN_COLOR_H)+3;
				ImageSkinButton.DrawImage(pDC,nXButtonPos-ImageSkinButton.GetWidth()/2,nYDrawPos-5);
				break;
			}
		case 1:		//饱和
			{
				DOUBLE dRectifyS=(m_CurrentRenderInfo.dRectifyS*100-MIN_COLOR_S)/(MAX_COLOR_S-MIN_COLOR_S);
				INT nXButtonPos=(INT)(nXDrawPos+(DOUBLE)(m_SizeColorItem.cx-6)*dRectifyS+3);
				ImageSkinButton.DrawImage(pDC,nXButtonPos-ImageSkinButton.GetWidth()/2,nYDrawPos-5);
				break;
			}
		case 2:		//亮度
			{
				DOUBLE dRectifyB=(m_CurrentRenderInfo.dRectifyB*100-MIN_COLOR_B)/(MAX_COLOR_B-MIN_COLOR_B);
				INT nXButtonPos=(INT)(nXDrawPos+(DOUBLE)(m_SizeColorItem.cx-6)*dRectifyB+3);
				ImageSkinButton.DrawImage(pDC,nXButtonPos-ImageSkinButton.GetWidth()/2,nYDrawPos-5);
				break;
			}
		}
	}

	//设置环境
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//绘画字符
	LPCTSTR pszCustom=TEXT("自我定制：");
	LPCTSTR pszRecommend=TEXT("推荐配色：");
	pDC->TextOut(10,102,pszCustom,lstrlen(pszCustom));
	pDC->TextOut(10,14,pszRecommend,lstrlen(pszRecommend));

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDC,0,0,SRCCOPY);

	//清理资源
	ImageBuffer.ReleaseDC();

	return;
}