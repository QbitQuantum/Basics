void CFolderListCtrl::CreateImageList()
{
	CImageList * pImgList = new CImageList;

	pImgList->Create( m_Properties.m_nItemCX, m_Properties.m_nItemCY, ILC_COLOR, 32, 32 );

	CDC * pdcThis = GetDC();
	CDC dcBmp; 
	CBitmap bmpRes;

	dcBmp.CreateCompatibleDC( pdcThis );
	bmpRes.CreateCompatibleBitmap( pdcThis, m_Properties.m_nItemCX, m_Properties.m_nItemCY );

	CBitmap * pbmpOld = static_cast<CBitmap*>(dcBmp.SelectObject( &bmpRes ));
	CRect r( 0, 0, m_Properties.m_nItemCX, m_Properties.m_nItemCY );
	LOGBRUSH lbBackground;

	ReleaseDC( pdcThis );
	lbBackground.lbColor = RGB( 255, 255, 255 );
	lbBackground.lbHatch = 0;
	lbBackground.lbStyle = BS_SOLID;
	
	CBrush brBackground;
	
	brBackground.CreateBrushIndirect( &lbBackground );

	dcBmp.FillRect( r, &brBackground );
	dcBmp.Rectangle( r );
	dcBmp.MoveTo( 0, 0 );
	dcBmp.LineTo( m_Properties.m_nItemCX, m_Properties.m_nItemCY );
	dcBmp.MoveTo( m_Properties.m_nItemCX, 0 );
	dcBmp.LineTo( 0, m_Properties.m_nItemCY );
	dcBmp.SelectObject( pbmpOld );
	dcBmp.DeleteDC();

	if( m_pimlThumbnails )
	{
		for( int i = m_pimlThumbnails->GetImageCount() - 1; i >= 0; i-- )
			m_pimlThumbnails->Remove( i );
		delete m_pimlThumbnails;
	}
	pImgList->Add( &bmpRes, RGB( 0, 0, 0 ) );
	m_pimlThumbnails = pImgList;
	if( m_flvtViewType == flvtThumbnail )
		SetImageList( pImgList, LVSIL_NORMAL );
}