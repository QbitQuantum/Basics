HBITMAP g_load_png_gdiplus_throw(HDC dc, const char * fn, unsigned target_cx, unsigned target_cy)
{
	//FIXME m_gdiplus_initialised = (Gdiplus::Ok == Gdiplus::GdiplusStartup(&m_gdiplus_instance, &Gdiplus::GdiplusStartupInput(), NULL));
	pfc::string8 canPath;
	HBITMAP bm = 0;

	abort_callback_dummy p_abort;
	file::ptr p_file;
	filesystem::g_get_canonical_path(fn, canPath);
	filesystem::g_open_read(p_file, canPath, p_abort);
	t_size fsize = pfc::downcast_guarded<t_size>(p_file->get_size_ex(p_abort));
	pfc::array_staticsize_t<t_uint8> buffer(fsize);
	p_file->read(buffer.get_ptr(), fsize, p_abort);
	p_file.release();

	IStream *pStream = NULL;
	HGLOBAL gd = GlobalAlloc(GMEM_FIXED | GMEM_MOVEABLE, buffer.get_size());
	if (gd == NULL)
		throw exception_win32(GetLastError());
	void * p_data = GlobalLock(gd);
	if (p_data == NULL)
	{
		GlobalFree(gd);
		throw exception_win32(GetLastError());
	}

	memcpy(p_data, buffer.get_ptr(), buffer.get_size());
	GlobalUnlock(gd);

	HRESULT hr = CreateStreamOnHGlobal(gd, TRUE, &pStream);
	if (FAILED(hr))
	{
		GlobalFree(gd);
		throw exception_win32(hr);
	}

	Gdiplus::Bitmap pImage(pStream);

	CheckGdiplusStatus() << pImage.GetLastStatus();
	{
		Gdiplus::BitmapData bitmapData;
		//Gdiplus::Bitmap * ppImage = &pImage;
		if (target_cx != pfc_infinite || target_cy != pfc_infinite)
		{
			Gdiplus::Bitmap pBitmapResized(target_cx == pfc_infinite ? pImage.GetWidth() : target_cx, target_cy == pfc_infinite ? pImage.GetHeight() : target_cy, PixelFormat32bppARGB);
			CheckGdiplusStatus() << pBitmapResized.GetLastStatus();
			Gdiplus::Graphics pGraphics(&pBitmapResized);
			CheckGdiplusStatus() << pGraphics.GetLastStatus();
			CheckGdiplusStatus() << pGraphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
			CheckGdiplusStatus() << pGraphics.SetInterpolationMode(Gdiplus::InterpolationModeBicubic);
			Gdiplus::ImageAttributes imageAttributes;
			CheckGdiplusStatus() << imageAttributes.SetWrapMode(Gdiplus::WrapModeTileFlipXY);
			CheckGdiplusStatus() << pGraphics.DrawImage(&pImage, Gdiplus::Rect(0, 0, pBitmapResized.GetWidth(), pBitmapResized.GetHeight()), 0, 0, pImage.GetWidth(), pImage.GetHeight(), Gdiplus::UnitPixel, &imageAttributes);

			CheckGdiplusStatus() << pBitmapResized.LockBits(&Gdiplus::Rect(0, 0, pBitmapResized.GetWidth(), pBitmapResized.GetHeight()), Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
			bm = g_CreateHbitmapFromGdiplusBitmapData32bpp(bitmapData);
			CheckGdiplusStatus() << pBitmapResized.UnlockBits(&bitmapData);
		}
		else
		{
			CheckGdiplusStatus() << pImage.LockBits(&Gdiplus::Rect(0, 0, pImage.GetWidth(), pImage.GetHeight()), Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
			//assert bitmapData.Stride == bitmapData.Width
			bm = g_CreateHbitmapFromGdiplusBitmapData32bpp(bitmapData);
			CheckGdiplusStatus() << pImage.UnlockBits(&bitmapData);
		}
	}
	return bm;

}