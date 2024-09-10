BOOL CShellIcons::Draw(CDC* pDC, int nIcon, int nSize, int nX, int nY, COLORREF crBack, COLORREF crBlend, UINT nStyle) const
{
	HIMAGELIST hImages;
	switch ( nSize )
	{
	case 16:
		hImages = m_i16.GetSafeHandle();
		break;
//	case 24:
//		hImages = m_i24.GetSafeHandle();
//		break;
	case 32:
		hImages = m_i32.GetSafeHandle();
		break;
	case 48:
		hImages = m_i48.GetSafeHandle();
		break;
	default:
		ASSERT( FALSE );
		return FALSE;
	}

	return ImageList_DrawEx( hImages, nIcon, pDC->GetSafeHdc(),
		nX, nY, nSize, nSize, crBack, crBlend, nStyle );
}