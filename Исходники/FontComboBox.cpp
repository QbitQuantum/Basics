void CFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	CString strText;
	//判断当前索引的字体名称是否为空
	int nIndex = lpDrawItemStruct->itemID;
	if (GetLBTextLen(nIndex) < 0)
		return ;
	GetLBText(nIndex, strText);
	ASSERT(!strText.IsEmpty());
	int nImage = 0;
	//根据索引值从m_pFontVec得到字体图像类型
	if (!m_pFontVec.empty())
		nImage = m_pFontVec[nIndex]->GetImage();
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();
	//如果Item处于选择焦点、状态下，用系统高亮色改变文本和背景色
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
		(lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	CRect     rItem(lpDrawItemStruct->rcItem);
	CRect     rText(rItem);
	CRect     rBmp(&rItem);
	if(m_FontBmp)
	{
		//计算Item中字体预览图的贴图位置
		rBmp.top +=  (rBmp.Height() - FNTIMG_Y) / 2;
		rBmp.bottom = rBmp.top + FNTIMG_Y + 1;
		rText.left += FNTIMG_X;
		if (nImage != (int)0XFF)
		{
			int x,y;
			x = nImage * FNTIMG_X;   //根据预览图类型计算源图的矩形大小
			y = FNTIMG_Y;
			CDC mdc;
			mdc.CreateCompatibleDC(&dc);
			CBitmap* pOldBmp = mdc.SelectObject(CBitmap::FromHandle(m_FontBmp));
			COLORREF clrTransparent = mdc.GetPixel(0, y);
			//调用TransparentBlt进行透明贴图，此函数需要加入MsImg32.Lib文件
			::TransparentBlt (dc.GetSafeHdc(),rBmp.left, rBmp.top, FNTIMG_X, FNTIMG_Y,  
				mdc, x, y, FNTIMG_X, FNTIMG_Y, clrTransparent);
		}
	}
	else
		rText.left += 10;
	//rText所代表的字体名称填充位置需要右移图片的宽度
	dc.DrawText(strText, rText, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);
	dc.Detach();
} 