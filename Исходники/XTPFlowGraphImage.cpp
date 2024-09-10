void CXTPFlowGraphImage::ImageChanged()
{
	CMDTARGET_RELEASE(m_pIcon);

	if (!m_pImage || m_pImage->GetLastStatus() != Gdiplus::Ok)
	{
		SAFE_DELETE(m_pImage);
	}

	m_szImage = CSize(0, 0);
	if (!m_pImage)
		return;

	m_szImage = CSize(m_pImage->GetWidth(), m_pImage->GetHeight());


	Gdiplus::PixelFormat eSrcPixelFormat = m_pImage->GetPixelFormat();
	UINT nBPP = 32;
	Gdiplus::PixelFormat eDestPixelFormat = PixelFormat32bppRGB;

	if( eSrcPixelFormat & PixelFormatGDI )
	{
		nBPP = Gdiplus::GetPixelFormatSize( eSrcPixelFormat );
		eDestPixelFormat = eSrcPixelFormat;
	}

	BOOL bAlpha = FALSE;
	if( Gdiplus::IsAlphaPixelFormat( eSrcPixelFormat ) )
	{
		nBPP = 32;
		bAlpha = TRUE;
		eDestPixelFormat = PixelFormat32bppARGB;
	}


	LPBYTE lpBits;
	HBITMAP hBitmap = CXTPImageManager::Create32BPPDIBSection(0, m_szImage.cx, m_szImage.cy, &lpBits);

	int nPitch = ( (((m_szImage.cx * nBPP)+31)/32)*4 );

	if( eDestPixelFormat == eSrcPixelFormat && nBPP == 32)
	{
		// The pixel formats are identical, so just memcpy the rows.
		Gdiplus::BitmapData data;
		Gdiplus::Rect rect( 0, 0, m_szImage.cx, m_szImage.cy );
		if(m_pImage->LockBits( &rect, Gdiplus::ImageLockModeRead, eSrcPixelFormat, &data )!=Gdiplus::Ok)
		{
			return;
		}

		size_t nBytesPerRow = XTPAlignUp( nBPP * m_szImage.cx, 8 )/8;
		BYTE* pbDestRow = static_cast< BYTE* >( lpBits );
		BYTE* pbSrcRow = static_cast< BYTE* >( data.Scan0 );
		for( int y = 0; y < m_szImage.cy; y++ )
		{
			MEMCPY_S(pbDestRow, pbSrcRow, nBytesPerRow);
			pbDestRow += nPitch;
			pbSrcRow += data.Stride;
		}

		m_pImage->UnlockBits( &data );
	}
	else
	{
		// Let GDI+ work its magic
		Gdiplus::Bitmap bmDest( m_szImage.cx, m_szImage.cy, nPitch, eDestPixelFormat, static_cast< BYTE* >( lpBits) );
		Gdiplus::Graphics gDest( &bmDest );

		gDest.DrawImage(m_pImage, 0, 0 );
	}

	CBitmap bmpIcons;
	bmpIcons.Attach(hBitmap);
	UINT nCommand[] = {0};

	m_pParent->GetImageManager()->SetIcons(bmpIcons, nCommand, 1, m_szImage, xtpImageNormal, bAlpha);

	m_pIcon = m_pParent->GetImageManager()->GetImage(nCommand[0], m_szImage.cx);

	if (m_pIcon)
	{
		m_pIcon->InternalAddRef();
	}

}