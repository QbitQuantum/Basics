//绘画界面
void CSkinWndObject::DrawSkinView(CDC * pDC)
{
	//获取参数
	CRect ClientRect;
	m_pWndHook->GetClientRect(&ClientRect);
    
	//建立缓冲图
	CSkinImage CaptionImage;
	CaptionImage.Create(ClientRect.Width(),m_SkinAttribute.m_nCaptionHeigth,24);
	if (CaptionImage.IsNull()) return;

	//绘画背景
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(NULL);
	BufferDC.SelectObject(CaptionImage);
	DrawCaption(&BufferDC,CaptionImage.GetWidth(),CaptionImage.GetHeight());
    
	//建立 DC
	if (pDC==NULL)
	{
		CClientDC ClientDC(m_pWndHook);
		ClientDC.BitBlt(m_nXExcursionPos,0,CaptionImage.GetWidth(),CaptionImage.GetHeight(),&BufferDC,0,0,SRCCOPY);
		//ClientDC.Draw3dRect(&ClientRect,RGB(0,0,0),RGB(0,0,0));
		BufferDC.DeleteDC();
	}
	else
	{
		pDC->BitBlt(m_nXExcursionPos,0,CaptionImage.GetWidth(),CaptionImage.GetHeight(),&BufferDC,0,0,SRCCOPY);
		//pDC->Draw3dRect(&ClientRect,RGB(0,0,0),RGB(0,0,0));
	}

	//获取标题
	TCHAR strTitle[128];
	GetWindowText(*m_pWndHook,strTitle,CountArray(strTitle));

	//计算位置
	INT nYPos=(m_SkinAttribute.m_nCaptionHeigth-12)/2+2;
	INT nXPos=35;

	//建立缓冲图
	CClientDC ClientDC(m_pWndHook);
	ClientDC.SetBkMode(TRANSPARENT);
	ClientDC.SelectObject(m_SkinAttribute.m_DefaultFont);
	ClientDC.SetTextAlign(TA_LEFT);	

	//变量定义
	int nStringLength=lstrlen(strTitle);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	int nXExcursion1=GetXExcursionPos();
	int nYExcursion1=GetYExcursionPos();

	CImageHandle m_FramLeft(&m_SkinAttribute.m_FramLeft);
	if (m_SkinAttribute.m_FramLeft.IsNull()) return ;
	CImageHandle m_BottomM(&m_SkinAttribute.m_BottomM);
	if (m_SkinAttribute.m_BottomM.IsNull()) return ;
	CImageHandle m_FramRight(&m_SkinAttribute.m_FramRight);
	if (m_SkinAttribute.m_FramRight.IsNull()) return ;

	CImageHandle BottomL(&m_SkinAttribute.m_BottomL);
	if (m_SkinAttribute.m_BottomL.IsNull()) return ;

	CImageHandle BottomR(&m_SkinAttribute.m_BottomR);
	if (m_SkinAttribute.m_BottomR.IsNull()) return ;


	int nLeftWidth=m_FramLeft->GetHeight();
	int nMidWidth=m_BottomM->GetWidth();
	int nRightWidth=m_FramRight->GetHeight();
    
	for (int i=ClientRect.top+CaptionImage.GetHeight();i<ClientRect.bottom-BottomL->GetHeight();i+=nLeftWidth)
		m_SkinAttribute.m_FramLeft.BitBlt(ClientDC,nXExcursion1,i);

	for (int i=ClientRect.top+CaptionImage.GetHeight();i<ClientRect.bottom-BottomR->GetHeight();i+=nRightWidth)
		m_SkinAttribute.m_FramRight.BitBlt(ClientDC,ClientRect.Width()-nXExcursion1-m_FramRight->GetWidth(),i);
    
	for (int i=nXExcursion1+BottomL->GetWidth();i<ClientRect.Width()-m_FramRight->GetWidth();i+=nMidWidth)
		m_SkinAttribute.m_BottomM.BitBlt(ClientDC,i,ClientRect.Height()-m_BottomM->GetHeight());
    
    m_SkinAttribute.m_BottomL.BitBlt(ClientDC,0,ClientRect.Height()-BottomL->GetHeight());
   
	m_SkinAttribute.m_BottomR.BitBlt(ClientDC,ClientRect.Width()-BottomR->GetWidth()-nXExcursion1,ClientRect.Height()-BottomR->GetHeight());
    
	//绘画边框
// 	ClientDC.SetTextColor(RGB(231,192,137));
// 	for (int i=0;i<CountArray(nXExcursion);i++)
// 	{
// 		ClientDC.TextOut(nXPos,nYPos,strTitle,nStringLength);
// 	}

	//CImageHandle TitleLeft1(&m_SkinAttribute.m_TitleLeft);
	//if (m_SkinAttribute.m_TitleLeft1.IsNull()) return ;
	//CImageHandle TitleMid1(&m_SkinAttribute.m_TitleMid);
	//if (m_SkinAttribute.m_TitleMid1.IsNull()) return ;
	//CImageHandle TitleRight1(&m_SkinAttribute.m_TitleRight);
	//if (m_SkinAttribute.m_TitleRight1.IsNull()) return ;

	//int nLeftWidth=TitleLeft1->GetHeight();
	//int nMidWidth=TitleMid1->GetWidth();
	//int nRightWidth=TitleRight1->GetWidth();
	/*for (int i=ClientRect.top;i<ClientRect.bottom;i+=nLeftWidth)
		TitleLeft1->BitBlt(BufferDC.m_hDC,ClientRect.left,i);*/
	/*for (int i=nLeftWidth;i<nXMinDrawPause;i+=nMidWidth) TitleMid1->BitBlt(pDC->m_hDC,i,0);
	TitleRight1->BitBlt(pDC->m_hDC,nXMinDrawPause,0);*/

	//绘画标题m_SkinAttribute.m_crCaptionTXColor
	//ClientDC.SetTextColor(m_SkinAttribute.m_crCaptionTXColor);
	//ClientDC.TextOut(nXPos,nYPos,strTitle);

	/*for (int i=ClientRect.top;i<ClientRect.bottom;i+=nLeftWidth)
		TitleLeft1->BitBlt(BufferDC.m_hDC,ClientRect.left,i);*/
	BufferDC.DeleteDC();

	return;
}