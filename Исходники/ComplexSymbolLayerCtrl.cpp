void CComplexSymbolLayerCtrl::InitComplexSymbolLayerCtrl(RECT * rect, 
														 UINT nIDResource , 
														 unsigned int nWidth)
{
	if( !rect )
	{
		return;
	}
	m_rc.bottom = rect->bottom - 5;
	m_rc.right = rect->right+1;
	m_rc.left = rect->left;
	m_rc.top = rect->top;
	m_nX = m_rc.right-m_rc.left;
	m_nY = m_rc.bottom-m_rc.top;
	if( m_LargeImageList!= NULL )
	{
		int nCount = m_LargeImageList->GetImageCount();
		for ( int i=0 ; nCount<i ; i++ )
		m_LargeImageList->Remove( i );
		m_LargeImageList->DeleteImageList();
		delete m_LargeImageList;
		m_LargeImageList=NULL;
	}
	m_LargeImageList=new CImageList;
	m_LargeImageList->Create(m_nX,m_nY,ILC_COLOR24,0,1);

	if( nIDResource!=-1 )
	{
		m_nWidth=nWidth;
		m_StateImageList.Create( nIDResource , nWidth , 1 , RGB(255,0,0) );
	}
	CDC * dc = GetDC();
	CDC MemDC;//创建相容的bitmap和dc

	HBITMAP hbitmap1 = CreateCompatibleBitmap( dc->GetSafeHdc() , m_nX , m_nY );
	HBITMAP hBitmapTemp;

	MemDC.CreateCompatibleDC(dc);
	hBitmapTemp = ( HBITMAP )SelectObject( MemDC , hbitmap1 );

	RECT rectMask;
	rectMask.top=rectMask.left= 0;
	rectMask.right = m_rc.right;
	rectMask.bottom = m_rc.bottom;

	HBRUSH hSolidBrush = CreateSolidBrush( DEFAULTCOLOR );
	FillRect( MemDC.GetSafeHdc() , &rectMask,hSolidBrush );
	hbitmap1=( HBITMAP )SelectObject( MemDC.m_hDC , hBitmapTemp );
	if(m_MaskBitmap!= NULL)
	{
		m_MaskBitmap->DeleteObject();
		m_MaskBitmap = NULL;
	}

	m_MaskBitmap=CBitmap::FromHandle( hbitmap1 );

	DeleteObject( hSolidBrush );
	ReleaseDC( dc );
	MemDC.DeleteDC();
	this->SetImageList( m_LargeImageList , LVSIL_NORMAL );
	this->SetImageList( &m_StateImageList , LVSIL_STATE );

	AddCOL();
}