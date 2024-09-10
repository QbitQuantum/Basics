void CEqualizerWnd::DrawButton(HDC _hDC)
{
	TString _tempstr;
	//	RECT _oPoint;

	if(m_MainWnd3)
	{
		SetRectEmpty(&m_rtOK);
		m_MainWnd3->m_Skincfg.FindConfig((TString)L"ÉèÖÃ_È·¶¨_Î»ÖÃ",_tempstr);
		CovertStr2Rect(_tempstr,&m_rtOK);
		m_MainWnd3->m_Skincfg.FindConfig((TString)L"ÉèÖÃ_È·¶¨_Õý³£",_tempstr);
		_tempstr = (TString)(m_MainWnd3->m_szUIBasePath) + _tempstr;
		DrawPngFromFile(_hDC,_tempstr.c_str(),&m_rtOK,RGB(0,0,0));


		SetRectEmpty(&m_rtCancel);
		m_MainWnd3->m_Skincfg.FindConfig((TString)L"ÉèÖÃ_È¡Ïû_Î»ÖÃ",_tempstr);
		CovertStr2Rect(_tempstr,&m_rtCancel);
		m_MainWnd3->m_Skincfg.FindConfig((TString)L"ÉèÖÃ_È¡Ïû_Õý³£",_tempstr);
		_tempstr = (TString)(m_MainWnd3->m_szUIBasePath) + _tempstr;
		DrawPngFromFile(_hDC,_tempstr.c_str(),&m_rtCancel,RGB(0,0,0));
	}
}