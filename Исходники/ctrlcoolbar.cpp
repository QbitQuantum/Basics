void CCoolBarItem::Paint(CDC* pDC, CRect& rc, BOOL bDown, BOOL bHot, BOOL bMenuGray, BOOL bTransparent)
{
	COLORREF crBackground;

	if ( m_nID == ID_SEPARATOR )
	{
		if ( ! bTransparent ) pDC->FillSolidRect( rc.left, rc.top, 3, rc.Height(), CoolInterface.m_crMidtone );
		pDC->Draw3dRect( rc.left + 3, rc.top, 1, rc.Height(), CoolInterface.m_crDisabled, CoolInterface.m_crDisabled );
		if ( ! bTransparent ) pDC->FillSolidRect( rc.left + 4, rc.top, 3, rc.Height(), CoolInterface.m_crMidtone );
		return;
	}

	if ( m_nCtrlID )
	{
		for ( int nShrink = rc.Height() - m_nCtrlHeight ; nShrink > 0 ; nShrink -= 2 )
		{
			if ( ! bTransparent ) pDC->Draw3dRect( &rc, CoolInterface.m_crMidtone, CoolInterface.m_crMidtone );
			rc.DeflateRect( 0, 1 );
		}
		rc.DeflateRect( 1, 0 );
	}
	else
	{
		if ( ! bTransparent ) pDC->Draw3dRect( &rc, CoolInterface.m_crMidtone, CoolInterface.m_crMidtone );
		rc.DeflateRect( 1, 1 );
	}

//	if ( ( m_bEnabled || m_nCtrlID ) && ( bHot || bDown || m_bChecked ) )
	if ( m_bEnabled && ( bHot || bDown || m_bChecked ) )
	{
		if ( bMenuGray && bDown )
		{
			pDC->Draw3dRect( &rc, CoolInterface.m_crDisabled, CoolInterface.m_crDisabled );
		}
		else
		{
			pDC->Draw3dRect( &rc, CoolInterface.m_crBorder, CoolInterface.m_crBorder );
		}

		rc.DeflateRect( 1, 1 );

		if ( bMenuGray && bDown )
		{
			crBackground = CoolInterface.m_crBackNormal;
		}
		else if ( m_bChecked )
		{
			crBackground = bHot ? CoolInterface.m_crBackCheckSel : CoolInterface.m_crBackCheck;
		}
		else
		{
			crBackground = bDown && bHot ? CoolInterface.m_crBackCheckSel : CoolInterface.m_crBackSel;
		}
	}
	else
	{
		if ( bTransparent )
		{
			crBackground = CLR_NONE;
		}
		else
		{
			crBackground = CoolInterface.m_crMidtone;
			pDC->Draw3dRect( &rc, crBackground, crBackground );
		}

		rc.DeflateRect( 1, 1 );
	}

	if ( m_nCtrlID )
	{
		if ( m_nCtrlHeight == CONTROL_HEIGHT )
		{
			pDC->Draw3dRect( &rc, CoolInterface.m_crWindow, CoolInterface.m_crWindow );
			rc.DeflateRect( 1, 1 );
		}
		return;
	}

	if ( crBackground == CLR_NONE )
	{
		pDC->SetBkMode( TRANSPARENT );
	}
	else
	{
		pDC->SetBkMode( OPAQUE );
		pDC->SetBkColor( crBackground );
	}

	if ( m_sText.GetLength() )
	{
		if ( m_crText != 0xFFFFFFFF )
			pDC->SetTextColor( m_crText );
		else if ( ! m_bEnabled )
			pDC->SetTextColor( CoolInterface.m_crDisabled );
		else if ( ( bHot || bDown || m_bChecked ) && ( ! bMenuGray || ! bDown ) )
			pDC->SetTextColor( CoolInterface.m_crCmdTextSel );
		else
			pDC->SetTextColor( CoolInterface.m_crCmdText );

		rc.left += ( m_nImage >= 0 ) ? 20 : 1;
		int nY = ( rc.top + rc.bottom ) / 2 - pDC->GetTextExtent( m_sText ).cy / 2 - 1;
		
		if ( crBackground == CLR_NONE ) 
			pDC->ExtTextOut( rc.left + 2, nY, ETO_CLIPPED, &rc, m_sText, NULL );
		else
			pDC->ExtTextOut( rc.left + 2, nY, ETO_CLIPPED|ETO_OPAQUE, &rc, m_sText, NULL );

		rc.right = rc.left;
		rc.left -= ( m_nImage >= 0 ) ? 20 : 1;
	}

	if ( m_nImage >= 0 )
	{
		CPoint ptImage( rc.left + 3, ( rc.top + rc.bottom ) / 2 - 8 );

		if ( ! m_bEnabled )
		{
			ImageList_DrawEx( CoolInterface.m_pImages.GetSafeHandle(), m_nImage, pDC->GetSafeHdc(),
				ptImage.x, ptImage.y, 0, 0, crBackground, CoolInterface.m_crShadow, ILD_BLEND50 );
			pDC->ExcludeClipRect( ptImage.x, ptImage.y, ptImage.x + 16, ptImage.y + 16 );
		}
		else if ( m_bChecked )
		{
			ImageList_DrawEx( CoolInterface.m_pImages.GetSafeHandle(), m_nImage, pDC->GetSafeHdc(),
				ptImage.x, ptImage.y, 0, 0, crBackground, CLR_NONE, ILD_NORMAL );
			pDC->ExcludeClipRect( ptImage.x, ptImage.y, ptImage.x + 16, ptImage.y + 16 );
		}
		else if ( ( bHot && ! bDown ) || ( bDown && ! bHot ) )
		{
			ptImage.Offset( 1, 1 );
			pDC->SetTextColor( CoolInterface.m_crShadow );
			ImageList_DrawEx( CoolInterface.m_pImages.GetSafeHandle(), m_nImage, pDC->GetSafeHdc(),
				ptImage.x, ptImage.y, 0, 0, crBackground, CLR_NONE, ILD_MASK );

			ptImage.Offset( -2, -2 );

			if ( crBackground != CLR_NONE )
			{
				pDC->FillSolidRect( ptImage.x, ptImage.y, 18, 2, crBackground );
				pDC->FillSolidRect( ptImage.x, ptImage.y + 2, 2, 16, crBackground );
			}

			ImageList_DrawEx( CoolInterface.m_pImages.GetSafeHandle(), m_nImage, pDC->GetSafeHdc(),
				ptImage.x, ptImage.y, 0, 0, CLR_NONE, CLR_NONE, ILD_NORMAL );

			pDC->ExcludeClipRect( ptImage.x, ptImage.y, ptImage.x + 18, ptImage.y + 18 );
		}
		else
		{
			ImageList_DrawEx( CoolInterface.m_pImages.GetSafeHandle(), m_nImage, pDC->GetSafeHdc(),
				ptImage.x, ptImage.y, 0, 0, crBackground, CoolInterface.m_crBackNormal,
				bDown ? ILD_NORMAL : ILD_BLEND25 );
			pDC->ExcludeClipRect( ptImage.x, ptImage.y, ptImage.x + 16, ptImage.y + 16 );
		}
	}
	
	if ( crBackground != CLR_NONE ) pDC->FillSolidRect( &rc, crBackground );
}