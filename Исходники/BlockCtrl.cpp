//-------------------------------------------------------------------//
// DrawBlocks()																		//
//-------------------------------------------------------------------//
// 
//-------------------------------------------------------------------//
void BlockCtrl::DrawBlocks( CDC *pDCa )
{
	// Get DC if no DC is passed
	CDC *pDC = pDCa;
	if(pDCa == NULL) pDC = GetDC();

	// Get the current screen measurements.
	BCScreenMeasurements bcsm;
	GetScreenMeasurements( bcsm );	

	// Create temporary work DC (memory DC) and bitmap
	CDC dcMem;
	CBitmap bmTemp;
	dcMem.CreateCompatibleDC(pDC);
	bmTemp.CreateCompatibleBitmap( 
		pDC,
		bcsm.rectClient.Width() + 2,
		bcsm.rectClient.Height() + 2
	);
	CBitmap *pbmOld = dcMem.SelectObject(&bmTemp);

	// Draw edge border, then exclude it.
	CBrush WorkSpaceBrush( GetSysColor( COLOR_BTNFACE ) );
	CBrush *pOldBrush = dcMem.SelectObject( &WorkSpaceBrush );
	CPen *pOldPen = (CPen *)dcMem.SelectStockObject( NULL_PEN );
	
	dcMem.Rectangle(&bcsm.rectClient);
	
	dcMem.Draw3dRect(
		&bcsm.rectClient,
		(COLORREF)GetSysColor(COLOR_3DSHADOW),
		(COLORREF)GetSysColor(COLOR_3DHILIGHT)
	);
	bcsm.rectClient.DeflateRect( 1, 1 );
	
	dcMem.Draw3dRect(
		&bcsm.rectClient,
		(COLORREF)GetSysColor(COLOR_3DDKSHADOW),
		(COLORREF)GetSysColor(COLOR_3DLIGHT)
	);

	dcMem.SelectStockObject( BLACK_PEN);

	// Draw the rows all the way to the clipping area.
	if ( bcsm.nRowDrawCount <= 0 || bcsm.nColDrawCount <= 0 )
		return;

	// Set up the scrollbar info.
	
	// If we can fit it all...
	if ( 
			m_nFirstDisplayedBlock == 0
		&&	bcsm.nRowDrawCount * bcsm.nColDrawCount >= GetBlockCount()
	) {
		m_BlockScrollbar.EnableWindow( FALSE );
	
	// Otherwise, set it up.
	} else
	{
		m_BlockScrollbar.EnableWindow( TRUE );
		m_si.nMax = GetBlockCount() / bcsm.nColDrawCount + 1;
		m_si.nPos = m_nFirstDisplayedBlock / bcsm.nColDrawCount;
		m_si.nPage = bcsm.nRowDrawCount;
		m_BlockScrollbar.SetScrollInfo( &m_si, FALSE );
	}

	// Position the scrollbar.
	m_BlockScrollbar.MoveWindow( bcsm.rectSB );

	//
	///////////////////////////////


	// Create clipping region.
	// This prevents us from drawing over the bottom and
	// right edges with minimal effort.
	CRgn rgnRect;
	rgnRect.CreateRectRgn( 
		bcsm.rectBC.left,
		bcsm.rectBC.top,
		bcsm.rectBC.right,
		bcsm.rectBC.bottom + cnXBorder - 2
	);
	dcMem.SelectClipRgn( &rgnRect );

	// Draw the blocks.

	// Create all the pens and brushes we will need.
	// Note that these will clean up after themselves when
	// they go out of scope.
	CPen penHighlighted		( PS_SOLID		, 1, cRGBHighlight	);
	CPen penSelected			( PS_DOT			, 1, cRGBSelected		);	// Options: PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_ALTERNATE
   
	// Did you define the BlockColorMap to match the BLOCK_COLORS enums?
	ASSERT( BLOCK_COLOR_COUNT == sizeof BlockColorMap / sizeof BlockColorMap[0] );

	vector<CBrush*> brushes;
	int nA;
	for ( nA = 0; nA < BLOCK_COLOR_COUNT; nA++ )
		brushes.push_back( new CBrush( BlockColorMap[ nA ] ) );

	// When the block control size is changed, the first block may no longer 
	// be a col-multiple.  Force it to be, so when the user scrolls back up,
	// they do not have a strange first line.
	if ( m_nFirstDisplayedBlock % bcsm.nColDrawCount != 0 )
		m_nFirstDisplayedBlock = ( m_nFirstDisplayedBlock / bcsm.nColDrawCount ) * bcsm.nColDrawCount;

	int nCurrentBlock = m_nFirstDisplayedBlock;
	BlockType btTemp;

	for ( nA = 0; nA < bcsm.nRowDrawCount && nCurrentBlock < GetBlockCount(); nA++ )
	{
		for ( int nB = 0; nB < bcsm.nColDrawCount && nCurrentBlock < GetBlockCount(); nB++ )
		{
			BlockType& btTemp = btvBlockData.at( nCurrentBlock );

			// Draw the block!

			// Reset to the background brush before we get started.
			dcMem.SelectObject( &WorkSpaceBrush );

			CRect rectBlock( 
				CPoint(
					bcsm.rectBC.left + nB * cnBlockWidth,
					bcsm.rectBC.top  + nA * cnBlockHeight
				),
				CSize(
					cnBlockWidth,
					cnBlockHeight
				)
			);

			// Already cleared the whole area.
			/*
			// Clear it first.
			dcMem.SelectObject( &WorkSpaceBrush );
			dcMem.SelectStockObject( NULL_PEN );
			dcMem.Rectangle( rectBlock );
			*/
			
			// Selected.
			if ( nCurrentBlock == m_nSelectedBlock )
			{
				dcMem.SelectObject( &penSelected );
				dcMem.Rectangle( rectBlock );
			}

			// Highlight.
			if ( btTemp.m_bcHighlight != BLOCK_COLOR_COUNT )
			{
				// TO DO
				// Rectangle() writes with current pen and brush
				// we may need to expand rect here to match previous results.
				// dcMem.SelectObject( &penHighlighted );
				
				
				// DEBUG
				rectBlock.InflateRect( 5, 5, 5, 5 );


				dcMem.SelectStockObject( NULL_PEN );
				dcMem.SelectObject( brushes[ btTemp.m_bcHighlight ] );
				
				// Don't overwrite the selected frame.
				if ( nCurrentBlock != m_nSelectedBlock )
					dcMem.Rectangle( rectBlock );
				

				// DEBUG
				rectBlock.DeflateRect( 5, 5, 5, 5 );


				rectBlock.DeflateRect( 1, 1, 1, 1 );
				dcMem.Rectangle( rectBlock );
				rectBlock.DeflateRect( 1, 1, 1, 1 );
			} else
				rectBlock.DeflateRect( 2, 2, 2, 2 );
			
			// Fill the rect.
			dcMem.SelectObject( brushes[ btTemp.m_bcColor ] );
			dcMem.SelectStockObject( NULL_PEN );
			dcMem.Rectangle( rectBlock );

			// Next, the partial fill.
			if ( 
					btTemp.m_bcPartialFill != BLOCK_COLOR_COUNT 
				&& btTemp.m_ubPercentFill > 0
			) {
				CRect rectPartial( rectBlock );
				rectPartial.top -= rectPartial.Height() * _MIN( 100 - btTemp.m_ubPercentFill, 0 ) / 100;
				dcMem.SelectObject( brushes[ btTemp.m_bcPartialFill ] );
				dcMem.SelectStockObject( NULL_PEN );
				dcMem.Rectangle( rectPartial );
			}
			
		   // Next, the 3D border.
		   dcMem.Draw3dRect(
				rectBlock, 
				
				// Top left    
				( nCurrentBlock == m_nSelectedBlock )
					?	(COLORREF)GetSysColor( COLOR_3DSHADOW	)
					:	(COLORREF)GetSysColor( COLOR_3DHILIGHT	),

				// Bottom right
				( nCurrentBlock == m_nSelectedBlock )
					?	(COLORREF)GetSysColor( COLOR_3DHILIGHT	)
					:	(COLORREF)GetSysColor( COLOR_3DSHADOW	)		
			);

			// Draw the 'X' as requested.
			if ( btTemp.m_bCrossedOut )
			{
				dcMem.SelectStockObject( BLACK_PEN);
				dcMem.MoveTo( rectBlock.left	+ 1, rectBlock.top		+ 1 );
				dcMem.LineTo( rectBlock.right - 1, rectBlock.bottom	- 1 );
				dcMem.MoveTo( rectBlock.right - 2, rectBlock.top		+ ( ( nCurrentBlock == m_nSelectedBlock ) ? 1 : 2 ) );
				dcMem.LineTo( rectBlock.left	+ ( ( nCurrentBlock == m_nSelectedBlock ) ? 0 : 1 ), rectBlock.bottom	- 1 );
			}

			// Maybe not the most efficient way, but pretty cheap...
			nCurrentBlock++;

		}

	}
	
	// Finally draw to the screen from dcMem.
	pDC->BitBlt(
		0,
		0,
		bcsm.rectClient.Width() + 2,
		bcsm.rectClient.Height() + 2,
		&dcMem,
		0,
		0,
		SRCCOPY
	);

	// Cleanup.
	dcMem.SelectObject(pOldBrush);
	WorkSpaceBrush.DeleteObject();
	dcMem.SelectObject(pbmOld);
	bmTemp.DeleteObject();
	dcMem.SelectObject(pOldPen);

	if ( pDCa == NULL ) 
		ReleaseDC( pDC );

	for ( nA = 0; nA < BLOCK_COLOR_COUNT; nA++ )
		delete brushes[nA];

}