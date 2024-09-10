HRESULT CDTDisplay::OnDrawAdvanced(ATL_DRAWINFO& di)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRunTime;
	GetAmbientUserMode(bRunTime);
	if(bRunTime)
	{//Draw Picture here Display the image data in the
		if(!m_DisplayImage.IsNull())
		{
			m_DisplayImage.Draw(di.hdcDraw,m_DrawRect,m_SrcRect);
		}
	}
	else
	{
		OLE_COLOR colorOle; 
		GetAmbientBackColor(colorOle); 
		COLORREF colorRgb; 
		::OleTranslateColor(colorOle,0,&colorRgb); 
		HBRUSH hBrush; 
		hBrush=CreateSolidBrush(colorRgb); 
		RECT& rc = *(RECT*)di.prcBounds; 
		FillRect(di.hdcDraw,&rc,hBrush); 
		DeleteObject(hBrush); 
		SetBkMode(di.hdcDraw,TRANSPARENT); 
		HICON hIcon=LoadIcon(_AtlBaseModule.GetResourceInstance(),MAKEINTRESOURCE(IDI_DISPLAY)); 
		DrawIcon(di.hdcDraw,rc.left,rc.top,hIcon); 
		DeleteObject(hIcon);
	}
	return 0;
	//return __super::OnDrawAdvanced(di);
}