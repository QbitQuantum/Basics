void CLibraryAlbumTrack::Paint(CLibraryAlbumView* pView, CDC* pDC, const CRect& rcTrack, int nCount)
{
	COLORREF crBack = m_bSelected ? Colors.m_crHighlight : CLibraryAlbumView::m_crRows[ nCount & 1 ];

	pDC->SetBkColor( crBack );
	pDC->SetTextColor( m_bSelected ? Colors.m_crHiText : Colors.m_crText );

	CRect rcLine( &rcTrack );
	rcLine.DeflateRect( 2, 1 );

	// Icon Box

	CRect rcTemp( rcLine.left, rcLine.top, rcLine.left + ICON_WIDTH, rcLine.bottom );
	rcLine.left += ICON_WIDTH;

	if ( nCount >= 0 )
		PaintText( pDC, rcTemp, 0, 100, NULL );

	ShellIcons.Draw( pDC, m_nShell, 16, rcTemp.left + 4,
		( rcTemp.top + rcTemp.bottom ) / 2 - 8, CLR_NONE, m_bSelected );

	// Rating Stars Box

	rcTemp.SetRect( rcLine.right - RATING_WIDTH, rcLine.top, rcLine.right, rcLine.bottom );
	rcLine.right -= RATING_WIDTH;

	CPoint ptStar( rcTemp.left + 4, ( rcTemp.top + rcTemp.bottom ) / 2 - 6 );
	PaintText( pDC, rcTemp, 0, 100, NULL, TRUE );

	if ( pView->m_pRating == this && m_nSetRating < 7 )
	{
		for ( int nRating = 2 ; nRating <= 6 ; nRating++ )
		{
			ImageList_DrawEx( pView->m_pStars, m_nSetRating >= nRating ? 2 : 1,
				*pDC, ptStar.x, ptStar.y, 12, 12,
				m_bSelected ? CLR_NONE : crBack, crBack,
				m_nSetRating >= nRating ? ILD_NORMAL : ILD_BLEND50 );
			ptStar.x += 12;
		}
	}
	else
	{
		for ( int nRating = 2 ; nRating <= 6 ; nRating++ )
		{
			ImageList_DrawEx( pView->m_pStars, m_nRating >= nRating ? 0 : 1,
				*pDC, ptStar.x, ptStar.y, 12, 12,
				m_bSelected ? CLR_NONE : crBack, crBack,
				m_nRating >= nRating ? ILD_NORMAL : ILD_BLEND50 );
			ptStar.x += 12;
		}
	}

	ptStar.x++;	// Comment icon gap

	if ( pView->m_pRating == this && m_nSetRating == 7 )
	{
		ImageList_DrawEx( pView->m_pStars, 5,
			*pDC, ptStar.x, ptStar.y, 12, 12, CLR_NONE, crBack, ILD_NORMAL );
	}
	else
	{
		ImageList_DrawEx( pView->m_pStars, m_bComments ? 3 : 4,
			*pDC, ptStar.x, ptStar.y, 12, 12,
			m_bSelected ? CLR_NONE : crBack, crBack,
			m_bComments ? ILD_NORMAL : ILD_BLEND50 );
	}

	// Metadata Boxes  (Available space %)

	if ( pView->m_pStyle == CSchema::uriMusicAlbum )
	{
		// Track, Title, Length, Bitrate
		PaintText( pDC, rcLine, 0, 5, &m_sTrack, TRUE );
		PaintText( pDC, rcLine, 5, 84, &m_sTitle );
		PaintText( pDC, rcLine, 84, 92, &m_sLength, TRUE );
		PaintText( pDC, rcLine, 92, 100, &m_sBitrate, TRUE );
	}
	else if ( pView->m_pStyle == CSchema::uriMusicArtist )
	{
		// Album, Title, Length, Bitrate
		PaintText( pDC, rcLine, 0, 30, &m_sAlbum );
		PaintText( pDC, rcLine, 30, 84, &m_sTitle );
		PaintText( pDC, rcLine, 84, 92, &m_sLength, TRUE );
		PaintText( pDC, rcLine, 92, 100, &m_sBitrate, TRUE );
	}
	else if ( pView->m_pStyle == CSchema::uriMusicAll ) // Genre
	{
		// Artist, Album, Title, Length, Bitrate
		PaintText( pDC, rcLine, 0, 25, &m_sArtist );
		PaintText( pDC, rcLine, 25, 50, &m_sAlbum );
		PaintText( pDC, rcLine, 50, 84, &m_sTitle );
		PaintText( pDC, rcLine, 84, 92, &m_sLength, TRUE );
		PaintText( pDC, rcLine, 92, 100, &m_sBitrate, TRUE );
	}
	else // Non-music
	{
		// Title, Artist, Length
		PaintText( pDC, rcLine,  0, 66, &m_sTitle );
		PaintText( pDC, rcLine, 66, 88, &m_sArtist );
		PaintText( pDC, rcLine, 88, 100, &m_sLength, TRUE );
	}
}