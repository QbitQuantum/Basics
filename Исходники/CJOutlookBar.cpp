void CCJOutlookBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC*            pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
    CRect           rcItem(lpDrawItemStruct->rcItem);
    CRect           rClient(rcItem);
    CRect           rText;
    CPoint          Pt(((rcItem.Width() - 32) /2 ), rcItem.top + 15);
    CContentItems   pContents = m_pContents[ lpDrawItemStruct->itemID ];
    HICON           hIcon = m_ImageListNormal.ExtractIcon( pContents.GetImageID());

	// deflate the client rect, and set up item and
	// text rect's.
	rClient.DeflateRect( 8, 5 );
	rcItem.CopyRect( rClient );
    rText.CopyRect( rClient );
    rText.top += 45;
	rText.bottom += 10;

    // set the text color to white, and background mode
	// to transparent.
	pDC->SetTextColor( ::GetSysColor( COLOR_WINDOW ) );
	pDC->SetBkMode( TRANSPARENT );

	// draw the button icon and text.
	if( lpDrawItemStruct->itemAction& ODA_DRAWENTIRE ) {
        pDC->DrawIcon( Pt, hIcon );
        pDC->DrawText( pContents.GetText(), rText,
			DT_CENTER | DT_WORDBREAK );
    }

    // if the left mouse button is pressed, offset
	// the button icon.
	if( m_bLBDown ) {
        Pt.x += 2;
        Pt.y += 2;
        rcItem.OffsetRect( 2, 2 );
    }

	// deflate the button rect, and move up.
	rcItem.DeflateRect( 4, 16 );
	rcItem.top -= 8;

	// Draw the button icon and text, if the mouse is over the
	// button, draw the 3d rect, either pressed,
	// or not pressed depending on left mouse button.
	if(( lpDrawItemStruct->itemState& ODS_SELECTED ) &&
		( lpDrawItemStruct->itemAction& ( ODA_SELECT | ODA_DRAWENTIRE ))) {
        
		rcItem.left = ( rcItem.Width()/2 )-5;
		rcItem.right = rcItem.left+37;

		if( m_bHilight ) {
            if( m_bLBDown ) {
              pDC->Draw3dRect( rcItem, ::GetSysColor( COLOR_3DDKSHADOW ),
				  ::GetSysColor( COLOR_BTNFACE ) );
			}
            else {
              pDC->Draw3dRect( rcItem, ::GetSysColor( COLOR_BTNFACE ),
				  ::GetSysColor( COLOR_3DDKSHADOW ) );
			}
        }

        pDC->DrawIcon( Pt, hIcon );
        pDC->DrawText( pContents.GetText(), rText,
			DT_CENTER | DT_WORDBREAK );
	}

	if( !( lpDrawItemStruct->itemState& ODS_SELECTED ) &&
		( lpDrawItemStruct->itemAction& ODA_SELECT )) {
        pDC->FillSolidRect( rClient, ::GetSysColor( COLOR_3DSHADOW ) );
        pDC->DrawIcon(Pt, hIcon);
        pDC->DrawText(pContents.GetText(), rText, DT_CENTER|DT_WORDBREAK);
    }
}