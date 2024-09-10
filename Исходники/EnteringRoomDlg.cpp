void CEnteringRoomDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if ( bShow )
	{		
		CString strDeferPicPath = DeferPicPathMgr->GetDefaultPicPathRandom() ;
		if ( m_pPic != NULL )
		{
			delete m_pPic ;
			m_pPic = NULL ;
		}
		m_pPic = new ImageEx( strDeferPicPath ) ;
		if ( m_pPic )
		{
			SetWindowPos( NULL , 0 , 0 , m_pPic->GetWidth() + m_imgMidLeft->GetWidth() * 2 + 1, 
				          m_pPic->GetHeight() + m_imgTopMid->GetHeight() * 2 + 1, SWP_NOMOVE ) ;
			/*SetWindowPos( NULL , 0 , 0 , m_pPic->GetWidth(), 
				m_pPic->GetHeight(), SWP_NOMOVE ) ;*/
			if (m_hrgn)
			{
				DeleteObject(m_hrgn);
			}
			CRect rc(0,0,0,0);
			GetClientRect(&rc);
			m_hrgn = CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 4, 4);
			SetWindowRgn(m_hrgn, TRUE);
			
			SetTimer( ENTER_ROOM_TIMER , 100 , NULL ) ;
		}
	}
	else
	{
		KillTimer( ENTER_ROOM_TIMER ) ;
	}
	// TODO: 在此处添加消息处理程序代码
	CenterWindow(m_pHallDlg); //居中显示
}