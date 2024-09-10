Surface8u convertGdiplusBitmap( Gdiplus::Bitmap &bitmap )
{	
	Gdiplus::BitmapData bitmapData;
	Gdiplus::Rect rect( 0, 0, bitmap.GetWidth(), bitmap.GetHeight() );

	Gdiplus::PixelFormat requestedFormat = bitmap.GetPixelFormat();
	SurfaceChannelOrder sco;
	bool premult;
	gdiplusPixelFormatToSurfaceChannelOrder( requestedFormat, &sco, &premult );
	if( sco == SurfaceChannelOrder::UNSPECIFIED ) {
		UINT flags = bitmap.GetFlags();
		sco = ( flags & Gdiplus::ImageFlagsHasAlpha ) ? SurfaceChannelOrder::BGRA : SurfaceChannelOrder::BGR;
		requestedFormat = ( flags & Gdiplus::ImageFlagsHasAlpha ) ? PixelFormat32bppARGB : PixelFormat24bppRGB;
	}
	
	bitmap.LockBits( &rect, Gdiplus::ImageLockModeRead, requestedFormat, &bitmapData );
	Surface8u result( bitmap.GetWidth(), bitmap.GetHeight(), sco.hasAlpha(), sco );

	const uint8_t *srcDataBase = (uint8_t*)bitmapData.Scan0;
	int32_t width = bitmap.GetWidth();
	for( uint32_t y = 0; y < bitmap.GetHeight(); ++y ) {
		memcpy( result.getData( Vec2i( 0, y ) ), srcDataBase + y * bitmapData.Stride, width * result.getPixelInc() );
	}

	bitmap.UnlockBits( &bitmapData );
	return result;
}