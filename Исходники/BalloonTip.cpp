void CBalloonTip::InitControls()
{
	CLabelUI * pLab = NULL;
	CButtonUI* pBtn = NULL;
	CTextUI	 * pText= NULL; 

	SIZE sz;GetDrawTextSize(m_strInfo,sz);
	if (sz.cx<9999&&sz.cy<300)
	{

		SetWindowPos(GetHWND(),HWND_TOPMOST,0,0,MAX(sz.cx+60,260),sz.cy+((m_dwMsgStyle!=0)?90:50),SWP_NOMOVE);
	}
	CRect rc;
	GetClientRect(GetHWND(),&rc);
	int nWidth = rc.GetWidth();
	int nHeight = rc.GetHeight();
	m_pPM->AddFont(MSYH,16,FALSE,FALSE,FALSE);

	int s = m_pPM->GetFontIndex(MSYH,16,FALSE,FALSE,FALSE);
	pLab = RegiserLabel(ID_LAB_TITLE,CRect(15,8,200,25),m_strTitle);
	if (pLab)
	{
		pLab->SetTextColor(RGB(73,73,73));
		pLab->SetText(m_strTitle);
		pLab->SetShowHtml(TRUE);
	}

	int nInfoStart = (nWidth - sz.cx)/2;
	pText = (CTextUI*)RegiserControl(CONTROL(CTextUI),ID_LAB_INFO,CRect(nInfoStart ,35,nWidth,40 + sz.cy));
	if (pText)
	{
		pText->SetShowHtml(TRUE);
		pText->SetText(m_strInfo);
		pText->SetTextColor(RGB(73,73,73));
		pText->SetTextStyle(DT_VCENTER|DT_LEFT);
	}

	pBtn = RegiserButton(ID_BTN_COSE,CRect(nWidth-31,2,nWidth-2,27));
	if (pBtn)
	{
		pBtn->SetImage(m_nClose);
	}
	if (m_dwMsgStyle != 0)
	{
		if ((m_dwMsgStyle & 0X0000000F) == MB_YESNO)
		{
			
			CButtonUI* pBtn = RegiserButton(ID_BTN_YES, CRect(30,sz.cy+50,120,sz.cy+80), _T("yes"));
			if (pBtn)
			{
				pBtn->SetImage( CUIMessageBox::m_nLeftBtnImage);
				pBtn->SetCorner(CRect(5,5,5,5));
			}
			pBtn = RegiserButton(ID_BTN_NO, CRect(nWidth - 120,sz.cy+50,nWidth - 30,sz.cy+80), _T("no"));
			if (pBtn)
			{
				pBtn->SetImage( CUIMessageBox::m_nLeftBtnImage);
				pBtn->SetCorner(CRect(5,5,5,5));
			}

		}
	}
}