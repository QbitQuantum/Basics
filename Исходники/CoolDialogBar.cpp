void CCoolDialogBar::DrawGripper(CDC & dc)
{
    // no gripper if floating
	if ( m_dwStyle & CBRS_FLOATING )
		return;

	// -==HACK==-
	// in order to calculate the client area properly after docking,
	// the client area must be recalculated twice (I have no idea why)
	m_pDockSite->RecalcLayout();
	// -==END HACK==-

	CRect gripper;
	GetWindowRect( gripper );
	ScreenToClient( gripper );
	gripper.OffsetRect( -gripper.left, -gripper.top );
	
	if ( m_dwStyle & CBRS_ORIENT_HORZ ) {
		
		// gripper at left
		m_rectGripper.top		= gripper.top + 40;
		m_rectGripper.bottom	= gripper.bottom;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right	= gripper.left + 20;

		// draw close box
		m_rectClose.left = gripper.left + 7;
		m_rectClose.right = m_rectClose.left + 12;
		m_rectClose.top = gripper.top + 10;
		m_rectClose.bottom = m_rectClose.top + 12;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);

		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(0,13);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.top += 38;
		gripper.bottom -= 10;
		gripper.left += 10;
		gripper.right = gripper.left+3;
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
		
		gripper.OffsetRect(4, 0);
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
	}
	
	else {
		
		// gripper at top
		m_rectGripper.top		= gripper.top;
		m_rectGripper.bottom	= gripper.top + 20;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right		= gripper.right - 40;

		// draw close box
		m_rectClose.right = gripper.right - 10;
		m_rectClose.left = m_rectClose.right - 11;
		m_rectClose.top = gripper.top + 7;
		m_rectClose.bottom = m_rectClose.top + 11;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);


		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(-13,0);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.right -= 38;
		gripper.left += 10;
		gripper.top += 10;
		gripper.bottom = gripper.top+3;
		dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
		
		gripper.OffsetRect(0, 4);
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
	}

}