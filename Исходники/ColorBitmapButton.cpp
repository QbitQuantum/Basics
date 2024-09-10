//-------------------------------------------------------------------//
// DrawItem()																			//
//-------------------------------------------------------------------//
// This function was copied from CBitmapButton's source (in 			//
// WinBtn.cpp). It was modified according to knowledge base article:	//
// "How to Use CBitmapButton to Resize a Bitmap to Fit a Button".		//
//-------------------------------------------------------------------//
void ColorBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	
	// Have to have loaded the bitmap.
	ASSERT( pBitmap->m_hObject != NULL );

	UINT state = lpDIS->itemState;

	// Update the style manually for checkbox-style buttons.
	if ( m_bCheckBoxStyle )
		if ( m_bCheckState )
			state |= ODS_SELECTED;
		else 
			state &= ~ODS_SELECTED;

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);

	// If we are Sizing to bitmap, then
	// the rectangle needs to be juuuuuust a little bit
	// bigger than the bitmap to leave room for the border.
	if ( uSizeToResourceID == 0 ) {

		// determine bitmaps size
		BITMAP bits;
		pBitmap->GetObject(sizeof(BITMAP),&bits);

		if ( bGrayedOut )
			rect.right = rect.left + (bits.bmWidth>>1) + 4;
		else