//界面绘画函数
void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//定义变量
	CRect ClientRect;
	GetClientRect(&ClientRect);
	bool bDisable=((lpDrawItemStruct->itemState&ODS_DISABLED)!=0);
	bool bButtonDown=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);

	//设置 DC
	HDC hDC=lpDrawItemStruct->hDC;

	//获取文字
	CString strText;
	GetWindowText(strText);

	//加载背景图
	CImageHandle ImageHandle;
	if (m_ImageBack.IsSetLoadInfo()) ImageHandle.AttachResource(&m_ImageBack);
	else ImageHandle.AttachResource(&m_SkinAttribute.m_ImageBack);
	if (ImageHandle.IsResourceValid())
	{
		//计算位图位置
		int iPartWidth=ImageHandle->GetWidth()/5,iDrawPos=0;
		if (bDisable) iDrawPos=iPartWidth*4;
		else if (bButtonDown) iDrawPos=iPartWidth;
		else if (m_bHovering) iDrawPos=iPartWidth*3;

		//绘画背景图
		if (m_bExpand==false) ImageHandle->BitBlt(hDC,0,0,ClientRect.Width(),ClientRect.Height(),iDrawPos,0,SRCCOPY);
		else ImageHandle->StretchBlt(hDC,0,0,ClientRect.Width(),ClientRect.Height(),iDrawPos,0,iPartWidth,ImageHandle->GetHeight(),SRCCOPY);
	}
	else
	{
		//绘画默认界面
		CDC * pDC=CDC::FromHandle(hDC);
		pDC->FillSolidRect(&ClientRect,GetSysColor(COLOR_BTNFACE));
		if (bButtonDown) pDC->Draw3dRect(&ClientRect,GetSysColor(COLOR_WINDOWFRAME),GetSysColor(COLOR_3DHILIGHT));
		else pDC->Draw3dRect(&ClientRect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_WINDOWFRAME));
	}

	//绘画图标
	if (bButtonDown) ClientRect.top+=2;
	if (m_hIcon)
	{
		DrawIconEx(hDC,ClientRect.left+6,ClientRect.top+(ClientRect.Height()-16)/2+1,m_hIcon,16,16,0,NULL,DI_NORMAL);
		ClientRect.left+=22;
	}

	//绘画字体
	ClientRect.top+=1;
	::SetBkMode(hDC,TRANSPARENT);
	if(!m_bShowTextFrame)
	{
		if (bDisable) ::SetTextColor(hDC,GetSysColor(COLOR_GRAYTEXT));
		else ::SetTextColor(hDC,m_crTextColor);
		DrawText(hDC,strText,strText.GetLength(),ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}
	//艺术字体
	else
	{
		CDC * pDC=CDC::FromHandle(hDC);
		DrawTextString(pDC,strText,m_crTextColor,m_crTextFrameColor,ClientRect);
	}

	return;
}