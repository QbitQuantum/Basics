void CBrowseTreeItem::Paint(CDC& dc, CRect& rc, BOOL bTarget, COLORREF crBack) const
{
	if ( crBack == CLR_NONE ) crBack = CoolInterface.m_crWindow;

	if ( m_nCount )
	{
		ImageList_DrawEx( ShellIcons.GetHandle( 16 ),
			m_bExpanded ? SHI_MINUS : SHI_PLUS,
			dc.GetSafeHdc(), rc.left, rc.top, 16, 16,
			crBack, CLR_NONE, ILD_NORMAL );
	}
	else
	{
		dc.FillSolidRect( rc.left, rc.top, 16, 16, crBack );
	}

	int nImage = ( m_bExpanded && m_nCount ) ? SHI_FOLDER_OPEN : SHI_FOLDER_CLOSED;
	if ( m_nIcon16 >= 0 ) nImage = m_nIcon16;

	UINT nIconStyle = ( m_bSelected || bTarget ) ? ILD_SELECTED : ILD_NORMAL;

	ImageList_DrawEx( ShellIcons.GetHandle( 16 ), nImage,
		dc.GetSafeHdc(), rc.left + 16, rc.top, 16, 16,
		crBack, CLR_DEFAULT, nIconStyle );

	crBack = ( m_bSelected || bTarget ) ? CoolInterface.m_crHighlight : crBack;
	COLORREF crText = ( m_bSelected || bTarget ) ? CoolInterface.m_crHiText : CoolInterface.m_crText;

	dc.SetTextColor( crText );
	dc.SetBkColor( crBack );
	dc.SetBkMode( OPAQUE );

	rc.left += 32;
	dc.ExtTextOut( rc.left + 3, rc.top + 1, ETO_OPAQUE|ETO_CLIPPED, &rc,
		m_sText, NULL );
	rc.left -= 32;
}