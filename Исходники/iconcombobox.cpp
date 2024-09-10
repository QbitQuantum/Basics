//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CIconComboBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CBrush *pOldBrush = NULL;
	CPen *pOldPen = NULL;

	//
	// the icon is "disabled"
	//
	if( !IsWindowEnabled() )
	{
		SetDisabledBrushAndPen( lpDrawItemStruct, &pOldBrush, &pOldPen );
        OnDrawIcon( lpDrawItemStruct );
		ResetBrushAndPen( lpDrawItemStruct, pOldBrush, pOldPen );
		return;
	}

	//
	// the icon is "selected"
	//
	if( ( lpDrawItemStruct->itemState & ODS_SELECTED ) && 
		( lpDrawItemStruct->itemAction & ( ODA_SELECT | ODA_DRAWENTIRE ) ) ) 
	{
		SetSelectedBrushAndPen( lpDrawItemStruct, &pOldBrush, &pOldPen );
		OnDrawIcon( lpDrawItemStruct );
		ResetBrushAndPen( lpDrawItemStruct, pOldBrush, pOldPen );
	}

	//
	// the icon is "un-selected"
	//
	if( !( lpDrawItemStruct->itemState & ODS_SELECTED ) && 
		 ( lpDrawItemStruct->itemAction & ( ODA_SELECT | ODA_DRAWENTIRE ) ) ) 
	{
		SetUnSelectedBrushAndPen( lpDrawItemStruct, &pOldBrush, &pOldPen );
		OnDrawIcon( lpDrawItemStruct );
		ResetBrushAndPen( lpDrawItemStruct, pOldBrush, pOldPen );
	}

	//
    // icon gains focus
	//
    if( lpDrawItemStruct->itemAction & ODA_FOCUS ) 
	{ 
		// get the device context
		CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

		// render the focus rectangle
        pDC->DrawFocusRect( &lpDrawItemStruct->rcItem );
    }
}