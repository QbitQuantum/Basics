void IcoSave(const std::wstring &fileName, HICON hicon)
{
	std::ofstream store(fileName.c_str(), std::ios_base::binary);
	if (!store.is_open())
		return;

	ICONINFO	ii;
	if (!GetIconInfo(hicon, &ii)) {
		store.close();
		return;
	}

	HBITMAP hbmMask = ii.hbmMask;
	HBITMAP hbmColor = ii.hbmColor;
	BITMAP  bmiMask;
	BITMAP  bmiColor;
	if (GetObject(hbmColor, sizeof(bmiColor), &bmiColor) &&
		GetObject(hbmMask, sizeof(bmiMask), &bmiMask) &&
		(bmiColor.bmWidth == bmiMask.bmWidth) &&
		(bmiColor.bmHeight == bmiMask.bmHeight) &&
		(bmiMask.bmHeight) > 0 &&
		(bmiMask.bmWidth) > 0) {
		BITMAPINFOHEADER  icobmi = { 0 };
		MYBITMAPINFO info1 = { 0 };
		MYBITMAPINFO info2 = { 0 };

		HDC hDC = CreateCompatibleDC(nullptr);
		info1.bmiHeader.biSize = sizeof(info1.bmiHeader);
		info1.bmiHeader.biWidth = bmiColor.bmWidth;
		info1.bmiHeader.biHeight = bmiColor.bmHeight;
		info1.bmiHeader.biPlanes = 1;
		info1.bmiHeader.biBitCount = bmiColor.bmBitsPixel;
		unsigned int size = GetDIBits(hDC, hbmColor, 0, info1.bmiHeader.biHeight, nullptr, (BITMAPINFO*)&info1, DIB_RGB_COLORS);
		char* bits1 = new char[info1.bmiHeader.biSizeImage];
		size = GetDIBits(hDC, hbmColor, 0, info1.bmiHeader.biHeight, bits1, (BITMAPINFO*)&info1, DIB_RGB_COLORS);
		info2.bmiHeader.biSize = sizeof(info2.bmiHeader);
		info2.bmiHeader.biWidth = bmiMask.bmWidth;
		info2.bmiHeader.biHeight = bmiMask.bmHeight;
		info2.bmiHeader.biPlanes = 1;
		info2.bmiHeader.biBitCount = bmiMask.bmBitsPixel;
		size = GetDIBits(hDC, hbmColor, 0, info1.bmiHeader.biHeight, nullptr, (BITMAPINFO*)&info2, DIB_RGB_COLORS);
		char* bits2 = new char[info2.bmiHeader.biSizeImage];
		size = GetDIBits(hDC, hbmMask, 0, info2.bmiHeader.biHeight, bits2, (BITMAPINFO*)&info2, DIB_RGB_COLORS);

		ICONDIR            icodir;
		ICONDIRENTRY      icoent;
		icodir.idReserved = 0;
		icodir.idType = 1;
		icodir.idCount = 1;

		icoent.bWidth = (unsigned char)bmiColor.bmWidth;
		icoent.bHeight = (unsigned char)bmiColor.bmHeight;
		icoent.bColorCount = 8 <= bmiColor.bmBitsPixel ? 0 : 1 << bmiColor.bmBitsPixel;
		icoent.bReserved = 0;
		icoent.wPlanes = bmiColor.bmPlanes;
		icoent.wBitCount = bmiColor.bmBitsPixel;
		icoent.dwBytesInRes = sizeof(BITMAPINFOHEADER) + info1.bmiHeader.biSizeImage + info2.bmiHeader.biSizeImage;

		icoent.dwImageOffset = sizeof(icodir) + sizeof(icoent);

		store.write((char*)&icodir, sizeof(icodir));
		store.write((char*)&icoent, sizeof(icoent));

		icobmi.biSize = sizeof(icobmi);
		icobmi.biWidth = bmiColor.bmWidth;
		icobmi.biHeight = bmiColor.bmHeight + bmiMask.bmHeight;
		icobmi.biPlanes = info1.bmiHeader.biPlanes;
		icobmi.biBitCount = bmiColor.bmBitsPixel;
		icobmi.biSizeImage = 0;

		store.write((char*)&icobmi, sizeof(icobmi));

		store.write(bits1, info1.bmiHeader.biSizeImage);
		store.write(bits2, info2.bmiHeader.biSizeImage);
		DeleteDC(hDC);
		delete[] bits1;
		delete[] bits2;
	}

	store.close();
	if (ii.hbmColor) DeleteObject(ii.hbmColor);
	if (ii.hbmMask) DeleteObject(ii.hbmMask);
}