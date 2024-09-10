BOOL SPRITE::SetColorKey( LONG Colors ){
	if ( Colors == CLR_INVALID )return TRUE;

	// マスクを不可視領域に作成
	// DirectDrawは、カラーキーセッティング
	if ( CompatibleDC ){
		for ( int j = 0 ; j < Size.cy ; j++ ){
			for ( int i = 0 ; i < Size.cx ; i++ ){
				LONG src = GetPixel( CompatibleDC , i , j );

				// 画面上半分は元画像（カラーキーにしたい色は黒へ、それ以外はcontinue)
				if ( src == Colors )
					SetPixelV( CompatibleDC , i , j , 0x0 );
				// 画面下半分はマスク分の画像
				SetPixelV( CompatibleDC , i , Size.cy + j , 
					( src == Colors ? 0xFFFFFF : 0x0 ) );
			}
		}
	}else if ( DDrawSurf ){
		HDC hDC ;SURFACEDESC ddsd; COLORREF PrevClr ; DWORD PhysicalClr;
		
		// GDIで、まずは点を打つ
		DDrawSurf->GetDC( &hDC );
		PrevClr = GetPixel( hDC , 0 , 0 );
		SetPixelV( hDC , 0 , 0 , Colors );
		DDrawSurf->ReleaseDC( hDC );

		// Lockを行い、直接アクセス。物理色の取得
		ZeroMemory( &ddsd , sizeof(ddsd) );ddsd.dwSize = sizeof( ddsd );
		while ( DDrawSurf->Lock( NULL, &ddsd, 0, NULL)  == DDERR_WASSTILLDRAWING );
		PhysicalClr = *( DWORD * )ddsd.lpSurface;	// 取得
		// Mask
		if ( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 ) 
			PhysicalClr &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;
		DDrawSurf->Unlock( NULL );

		// 元の色をリストア
		DDrawSurf->GetDC( &hDC );
		SetPixelV( hDC , 0 , 0 , PrevClr );
		DDrawSurf->ReleaseDC ( hDC );

		DDCOLORKEY ddck = { PhysicalClr , PhysicalClr };

		DDrawSurf->SetColorKey( DDCKEY_SRCBLT , &ddck );
	}
	CLRKey = Colors;

	return TRUE;
}