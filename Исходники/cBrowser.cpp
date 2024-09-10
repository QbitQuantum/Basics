//---중요!!! 다이얼로그가 액티브상태가 아니라 그려지 않으면 원래 하위 게임유아이들도 그려지지 않으나,
//---이 브라우저는 윈도우가 뜨는 것이라 꼭 액티브상태를 꺼줘야한다.
//---따라서 cDialog::SetActiveRecursive() 를 사용하라. 
//---void CItemShopDlg::SetActive( BOOL val ) 참고.
void cBrowser::SetActive(BOOL val)
{
	if(IsDisable())
	{
		return;
	}
	
	m_bActive = val;

	if(val)
	{
		// 091221 LUJ, 맵 이동 시 종종 cBrowser의 소멸자 호출 시에
		//			ATL 오류가 발생한다. m_hwndIE가 사용되지 않은
		//			핸들로 나타난다. 오류 빈도를 줄이기 위해 창을
		//			열때에만 창을 생성하도록 수정
		if(0 == m_hwndIE)
		{
			m_hwndIE = CreateWindow(
				"AtlAxWin71",
				"about:blank",
				FULLSCREEN_WITH_BLT == GAMERESRCMNGR->GetResolution().dispType ? WS_POPUP : WS_CHILD,
				int(GetAbsX()),
				int(GetAbsY()),
				GetWidth(),
				GetHeight(),
				_g_hWnd,
				0,
				GetModuleHandle(0),
				0);
			CComPtr<IUnknown> punkIE = 0;

			if(S_OK == AtlAxGetControl(
				m_hwndIE,
				&punkIE))
			{
				m_pWebBrowser = punkIE;
			}
		}

		ShowWindow(
			m_hwndIE,
			SW_SHOW);
	}
	else
	{
		if(m_hwndIE)
		{
			ShowWindow(
				m_hwndIE,
				SW_HIDE);
		}
	}
}