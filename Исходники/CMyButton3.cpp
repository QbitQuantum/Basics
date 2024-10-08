void CMyButton3::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//得到绘制的设备环境CDC
	VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

	// 得当Button上文字,这里的步骤是:1,先得到在资源里编辑的按钮的文字,
	//然后将此文字重新绘制到按钮上,
	//同时将此文字的背景色设为透明,这样,按钮上仅会显示文字
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	int size=strlen(buffer);   //得到长度
	DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //绘制文字
	SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);   //透明

	if (lpDrawItemStruct->itemState &ODS_SELECTED)  //当按下按钮时的处理
	{//
		//重绘整个控制
		CBrush brush(m_DownColor);  
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//因为这里进行了重绘,所以文字也要重绘
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
	}
	else                     //当按钮不操作或者弹起时
	{
		CBrush brush(m_UpColor);     
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//同上,进行重绘文字
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);    
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
	}
	if ((lpDrawItemStruct->itemState &ODS_SELECTED)&&(lpDrawItemStruct->itemAction &(ODA_SELECT| ODA_DRAWENTIRE)))
	{   //选中了本控件,高亮边框
		COLORREF fc=RGB(255-GetRValue(m_UpColor),255-GetGValue(m_UpColor), 255-             GetBValue(m_UpColor));//
		CBrush brush(fc);//
		dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);//
	}
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//控制的选中状态结束,去掉边框
		CBrush brush(m_UpColor);
		dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);//
	}
	dc.Detach();//
}