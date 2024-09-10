// 自绘, 灯亮LightOn=true(按钮显示第二幅图),否则LightOn=false(按钮显示第一幅图),
// 控件失效，即未使能，显示第三幅图片
void CLightBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	ASSERT(lpDrawItemStruct != NULL); 
	// must have at least the first bitmap loaded before calling DrawItem 
	ASSERT(m_bitmap.m_hObject != NULL);     // 至少有一个正常显示的CBitmap对象 

	CBitmap* pBitmap = &m_bitmap; // 第一个图片正常显示(Light off)
	UINT state = lpDrawItemStruct->itemState; 

	if ((state & ODS_DISABLED) && m_bitmapFocus.m_hObject != NULL) 
		pBitmap = &m_bitmapFocus;   // 第三个图片用于未使能按钮(disable)
	else if(m_LightOn && m_bitmapSel.m_hObject != NULL)
		pBitmap = &m_bitmapSel; // 第二个图片，左键按下后显示(Light on)

	// draw the whole button 
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 
	CDC memDC; 
	memDC.CreateCompatibleDC(pDC); 
	CBitmap* pOld = memDC.SelectObject(pBitmap); 
	if (pOld == NULL) 
		return;     // destructors will clean up 

	CRect rect; 
	rect.CopyRect(&lpDrawItemStruct->rcItem); 
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), 
		&memDC, 0, 0, SRCCOPY); 
	memDC.SelectObject(pOld); 
}