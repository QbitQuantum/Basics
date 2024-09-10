void ClauncherDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        // draw background image
        CDC dcMemory;
        dcMemory.CreateCompatibleDC(GetDC());

        CBitmap bitmap;
        // bitmap.LoadBitmap( IDB_BITMAP1 ); // eng
        // bitmap.LoadBitmap( IDB_BITMAP3 ); // ru
        // bitmap.LoadBitmap( IDB_BITMAP4 ); // de
        bitmap.LoadBitmap( IDB_BITMAP5 ); // pl
        CBitmap *pbmOriginal = dcMemory.SelectObject(&bitmap);

        // draw bitmap
        GetDC()->BitBlt( 0,0,640,480, &dcMemory, 0,0, SRCCOPY );

        // invalidate all controls
        m_Adapter.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_VideoMode.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_Fullscreen.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_Sync.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_AfterFx.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_SkinShader.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_Grass.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_Crowd.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_Traffic.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_MusicVolume.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Left.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Right.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Up.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Down.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_LeftSkew.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_RightSkew.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_JumpPull.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_RunTrack.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_AltimeterMode.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_IncreaseWA.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_DecreaseWA.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_WLO.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Hook.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_FirstPerson.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_External.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_Flyby.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_SwitchHUD.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_IncreaseTime.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_DecreaseTime.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_IncreaseMusic.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        mctrl_DecreaseMusic.RedrawWindow( NULL, NULL, RDW_INVALIDATE );
        m_StartButton.RedrawWindow( NULL, NULL, RDW_INVALIDATE );

        // draw all
        CDialog::OnPaint();
	}
}