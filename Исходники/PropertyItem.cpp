//绘画函数
void CPropertyItem::OnPaint()
{
	CPaintDC dc(this); 

	//绘画标题
	DrawCaption(&dc);

	//获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);
	int nXExcursion=GetXExcursionPos();
	int nYExcursion=GetYExcursionPos();

	//绘画背景
	COLORREF Color = /*RGB(0,51,102)*/RGB(115,181,239);
	dc.FillSolidRect(nXExcursion,nYExcursion,ClientRect.Width()-2*nXExcursion,4,Color);
	dc.FillSolidRect(nXExcursion,ClientRect.Height()-8,ClientRect.Width()-2*nXExcursion,7,Color);
	dc.FillSolidRect(nXExcursion,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,Color);
	dc.FillSolidRect(ClientRect.Width()-nXExcursion-12,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,Color);

	//绘画边框
	DrawBorder(&dc);

	//道具图片
	CBitmap Bitmap;

	//加载图片
	AfxSetResourceHandle(CPropertyBar::m_pPropertyBar->m_ReshInstance);
	if ( Bitmap.LoadBitmap(CPropertyBar::m_pPropertyBar->m_PropertyViewImage.uPropertyFormer[m_nPropertyID]) )
	{
		//创建资源
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap *pOldBitmap = dcMem.SelectObject(&Bitmap);

		//绘画图片
		BITMAP bm;
		Bitmap.GetBitmap(&bm);
		dc.TransparentBlt(10, 28+5, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight,RGB(255,255,255)); 
		
		//是否资源
		dcMem.SelectObject(pOldBitmap);
		Bitmap.DeleteObject();
		dcMem.DeleteDC();
	}
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//获取位置
	CRect rcStaticName, rcStaticDes;
	GetDlgItem(IDC_PROPERTY_NAME)->GetWindowRect(rcStaticName);
	GetDlgItem(IDC_PROPERTY_DESCRIBE)->GetWindowRect(rcStaticDes);
	ScreenToClient(&rcStaticName);
	ScreenToClient(&rcStaticDes);

	//设置内容
	CRect rcPropertyName(rcStaticName.right+3, rcStaticName.top, rcStaticName.right+200, rcStaticName.bottom+100);
	CRect rcPropertyDes(rcStaticDes.right+3, rcStaticDes.top, rcStaticDes.right+200, rcStaticDes.bottom+70);
	if(m_nPropertyID>=PROP_MEMBER_1)rcPropertyDes.right+=30;

	//创建字体
	CFont font;
	VERIFY(font.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename

	//设置属性
	dc.SetBkMode(TRANSPARENT);
	CFont* def_font = dc.SelectObject(&font);
	
	//描述信息
	UINT nFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	dc.DrawText(g_PropertyDescribe[m_nPropertyID].szName, rcPropertyName, nFormat);
	dc.DrawText(g_PropertyDescribe[m_nPropertyID].szDescribe, rcPropertyDes, nFormat);

	//删除资源
	dc.SelectObject(def_font);
	font.DeleteObject();
}