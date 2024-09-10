HRESULT LiferayNativityContextMenus::_ConvertBufferToPARGB32(HPAINTBUFFER hPaintBuffer, HDC hdc, HICON hicon, SIZE& sizIcon)
{
	RGBQUAD *prgbQuad;
	int cxRow;
	HRESULT hResult = GetBufferedPaintBits(hPaintBuffer, &prgbQuad, &cxRow);

	if (SUCCEEDED(hResult))
	{
		Gdiplus::ARGB *pargb = reinterpret_cast<Gdiplus::ARGB *>(prgbQuad);

		if (!_HasAlpha(pargb, sizIcon, cxRow))
		{
			ICONINFO info;

			if (GetIconInfo(hicon, &info))
			{

				if (info.hbmMask)
				{
					hResult = _ConvertToPARGB32(hdc, pargb, info.hbmMask, sizIcon, cxRow);
				}

				DeleteObject(info.hbmColor);
				DeleteObject(info.hbmMask);
			}
		}
	}

	return hResult;
}