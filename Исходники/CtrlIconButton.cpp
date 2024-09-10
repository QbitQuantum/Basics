void CIconButtonCtrl::OnPaint()
{
	CPaintDC dc( this );
	BOOL bSkinned( FALSE );
	COLORREF crBack( CLR_NONE );
	CString strText;
	CPoint ptIcon;
	CRect rc;

	GetClientRect( &rc );
	GetWindowText( strText );

	BOOL bTextButton = ( strText.IsEmpty() == false );

	ptIcon.x = bTextButton ? ( rc.left + 5 ) : ( ( rc.left + rc.right ) / 2 - 8 );		// Rich Button (left) or Icon Button (centered)
	ptIcon.y = ( rc.top + rc.bottom ) / 2 - 8;

	if ( rc.Width() < 20 || rc.Height() < 20 )		// Don't skin special case small buttons
	{
		dc.FillSolidRect( ptIcon.x - 1, ptIcon.y - 1, rc.right + 1, rc.bottom + 1, Colors.m_crTaskBoxClient );

		if ( m_bDown != m_bCapture ) ptIcon.Offset( -1, -1 );

		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, CLR_NONE, CLR_NONE,
			( ! IsWindowEnabled() || ( m_bDown && m_bCapture ) ) ? ILD_BLEND50 : ILD_NORMAL );

		return;
	}

	if ( m_bDown && m_bCapture )		// Pressed
	{
		if ( ! bTextButton && Images.DrawButtonState( &dc, &rc, ICONBUTTON_PRESS ) ) 	// IconButton.Press
		{
			bSkinned = TRUE;
		}
		else if ( Images.DrawButtonState( &dc, &rc, RICHBUTTON_PRESS ) ) 				// RichButton.Press
		{
			dc.SetBkMode( TRANSPARENT );
			bSkinned = TRUE;
			rc.left++;
		}
		else
		{
			dc.Draw3dRect( &rc, Colors.m_crBorder, Colors.m_crBorder );
			crBack = Colors.m_crBackCheckSel;
			rc.DeflateRect( 1, 1 );
		}

		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, crBack, CLR_NONE, ILD_BLEND50 );
	}
	else if ( m_bDown != m_bCapture )	// Hover  (or Unpressed)
	{
		if ( ! bTextButton && Images.DrawButtonState( &dc, &rc, ICONBUTTON_HOVER ) ) 	// IconButton.Hover
		{
			bSkinned = TRUE;
		}
		else if ( Images.DrawButtonState( &dc, &rc, RICHBUTTON_HOVER ) )					// RichButton.Hover
		{
			dc.SetBkMode( TRANSPARENT );
			bSkinned = TRUE;
			rc.left++;
		}
		else
		{
			dc.Draw3dRect( &rc, Colors.m_crBorder, Colors.m_crBorder );
			crBack = Colors.m_crBackSel;
			rc.DeflateRect( 1, 1 );

			ptIcon.Offset( -1, -1 );
			dc.FillSolidRect( ptIcon.x, ptIcon.y, 18, 2, crBack );
			dc.FillSolidRect( ptIcon.x, ptIcon.y + 2, 2, 16, crBack );

			ptIcon.Offset( 2, 2 );
			dc.SetTextColor( Colors.m_crShadow );
			ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
				ptIcon.x, ptIcon.y, 0, 0, crBack, CLR_NONE, ILD_MASK );

			ptIcon.Offset( -1, -1 );
		}

		ptIcon.Offset( -1, -1 );
		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, CLR_NONE, CLR_NONE, ILD_NORMAL );

		dc.ExcludeClipRect( ptIcon.x, ptIcon.y, ptIcon.x + 16, ptIcon.y + 16 );
		ptIcon.Offset( 1, 1 );
	}
	else if ( IsWindowEnabled() && GetFocus() == this ) 	// Button w/ Cursor Focus
	{
		if ( ! bTextButton && Images.DrawButtonState( &dc, &rc, ICONBUTTON_ACTIVE ) )	// IconButton.Active
		{
			bSkinned = TRUE;
		}
		else if ( Images.DrawButtonState( &dc, &rc, RICHBUTTON_ACTIVE ) )				// RichButton.Active
		{
			dc.SetBkMode( TRANSPARENT );
			bSkinned = TRUE;
			rc.left++;
		}
		else
		{
			dc.Draw3dRect( &rc, Colors.m_crBorder, Colors.m_crBorder );
			crBack = Colors.m_crBackNormal;
			rc.DeflateRect( 1, 1 );
		}

		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, crBack, CLR_NONE, ILD_NORMAL );
	}
	else if ( IsWindowEnabled() )	// Button Default w/o Focus
	{
		if ( ! bTextButton && Images.DrawButtonState( &dc, &rc, ICONBUTTON_DEFAULT ) )	// IconButton
		{
			bSkinned = TRUE;
		}
		else if ( Images.DrawButtonState( &dc, &rc, RICHBUTTON_DEFAULT ) )				// RichButton
		{
			dc.SetBkMode( TRANSPARENT );
			bSkinned = TRUE;
			rc.left++;
		}
		else
		{
			dc.Draw3dRect( &rc, Colors.m_crShadow, Colors.m_crShadow );
			crBack = Colors.m_crBackNormal;
			rc.DeflateRect( 1, 1 );
		}

		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, crBack, CLR_NONE, ILD_NORMAL );
	}
	else	// Disabled
	{
		if ( ! bTextButton && Images.DrawButtonState( &dc, &rc, ICONBUTTON_DISABLED ) )	// IconButton.Disabled
		{
			bSkinned = TRUE;
		}
		else if ( Images.DrawButtonState( &dc, &rc, RICHBUTTON_DISABLED ) )				// RichButton.Disabled
		{
			dc.SetBkMode( TRANSPARENT );
			bSkinned = TRUE;
			rc.left++;
		}
		else
		{
			dc.Draw3dRect( &rc, Colors.m_crShadow, Colors.m_crShadow );
			crBack = Colors.m_crMidtone;
			rc.DeflateRect( 1, 1 );
		}

		dc.SetTextColor( Colors.m_crDisabled );
		dc.SetBkColor( crBack );

		ImageList_DrawEx( m_pImageList.m_hImageList, 0, dc.GetSafeHdc(),
			ptIcon.x, ptIcon.y, 0, 0, crBack, Colors.m_crDisabled, ILD_BLEND50 );	// CLR_NONE, ILD_MASK ?
	}

	if ( ! bSkinned )
		dc.ExcludeClipRect( ptIcon.x, ptIcon.y, ptIcon.x + 16, ptIcon.y + 16 );

	if ( bTextButton )	// strText
	{
		rc.left += ptIcon.x + 16 + 2;	// Text Offset

		CFont* pOldFont = (CFont*)dc.SelectObject( &CoolInterface.m_fntNormal );

		if ( ! bSkinned )
			dc.SetBkColor( crBack );
		dc.SetTextColor( IsWindowEnabled() ? Colors.m_crCmdText : Colors.m_crDisabled );
		dc.ExtTextOut( rc.left, ptIcon.y + 1, ETO_CLIPPED|( ! bSkinned ? ETO_OPAQUE : 0 ), &rc, strText, NULL );
		dc.SelectObject( pOldFont );

		if ( ! bSkinned )	// Fill icon area not covered by opaque text
			dc.FillSolidRect( rc.left - ( ptIcon.x + 16 + 2 ), rc.top, rc.left, rc.bottom - 1, crBack );
	}
	else if ( ! bSkinned )
		dc.FillSolidRect( &rc, crBack );
}