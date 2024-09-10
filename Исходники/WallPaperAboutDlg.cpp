/*
	OnTimer()

	Chiamata per ogni tick del timer.
*/
void CWallPaperAboutDlg::OnTimer(UINT nID)
{
	if(nID==ID_TIMER_SPLASH_SCREEN)
	{
		// ancora non invisibile
		if(m_nLayerValue >= LWA_ALPHA_INVISIBLE_THRESHOLD/*LWA_ALPHA_INVISIBLE*/)
		{
			// usa il flag per evitare lo sfarfallio/fondo nero iniziali
			if(!IsVisible())
			{
				CenterWindow();
				::SetForegroundWindowEx(this->m_hWnd);
				SetVisible(TRUE);
				this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
				GetDlgItem(IDC_STATIC_WEBSITE)->SetFocus();
			}
			else
			{
				if(++m_nTimerCalls > 0)
				{
					if(!m_nScrolled)
					{
						CWnd* pWnd = GetDlgItem(IDC_EDIT_ABOUT);
						if(pWnd)
						{
							SCROLLINFO si = {0};
							si.cbSize = sizeof(si);
							si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
							pWnd->GetScrollInfo(SB_VERT,&si,SIF_ALL);
							
							if(si.nPos > m_nScrollPos || (si.nPos==m_nScrollPos && m_nScrollPos==0))
							{
								m_nScrollPos = si.nPos;
								pWnd->SendMessage(WM_VSCROLL,SB_LINEDOWN);
								m_nScrolled = 1;
							}
						}
					}
					else
						m_nScrolled = 0;
				}

				// imposta la trasparenza
				m_wndLayered.SetLayer(this->m_hWnd,(BYTE)m_nLayerValue);
				int nFactor = 1;
				if(m_nLayerValue >= LWA_ALPHA_OPAQUE/2)
					nFactor = 1;
				else if(m_nLayerValue >= LWA_ALPHA_OPAQUE/3)
					nFactor = 2;
				else if(m_nLayerValue >= LWA_ALPHA_OPAQUE/4)
					nFactor = 4;//3;
				else
					nFactor = 7;//5;
				m_nLayerValue -= nFactor;
			}
		}
		else
		{
			// dialogo invisibile, termina
			KillTimer(m_nTimerId),m_nTimerId = 0L;
			::PostMessage(this->m_hWnd,WM_COMMAND,MAKELONG(IDCANCEL,0),0L);
		}
	}

	CDialogEx::OnTimer(nID);
}