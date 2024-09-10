void BCGPResizeImage32
(
	CBCGPToolBarImages& imageSrc,
	CBCGPToolBarImages& imageDst,
	int index,
	CBCGPToolBarImages::ImageAlignHorz horz,
	CBCGPToolBarImages::ImageAlignVert vert,
	CBCGPZoomKernel::XFilterType ft
)
{
	CSize sizeSrc (imageSrc.GetImageSize ());
	CSize sizeDst (imageDst.GetImageSize ());

	imageDst.Clear ();
	imageDst.SetPreMultiplyAutoCheck (TRUE);
	imageDst.SetTransparentColor ((COLORREF) -1);
	imageDst.SetImageSize (sizeDst);

	if (sizeSrc != sizeDst)
	{
		CSize size (sizeDst);

		if (horz == CBCGPToolBarImages::ImageAlignHorzStretch)
		{
			size.cx = sizeSrc.cx;
		}
		if (vert == CBCGPToolBarImages::ImageAlignVertStretch)
		{
			size.cy = sizeSrc.cy;
		}

		int nStart = 0;
		int nEnd   = imageSrc.GetCount ();
		if (index != -1)
		{
			nStart = index;
			nEnd   = nStart + 1;
		}

		for (int i = nStart; i < nEnd; i++)
		{
			CMemoryDC dc;
			dc.SetSize (size);
			CBitmap* bmpImage = &dc.GetBitmap ();

			imageSrc.DrawEx (&dc.GetDC (), CRect (CPoint (0, 0), size), i, horz, vert);

			CMemoryDC dcImage;

			if (horz == CBCGPToolBarImages::ImageAlignHorzStretch ||
				vert == CBCGPToolBarImages::ImageAlignVertStretch)
			{
				dcImage.SetSize (sizeDst);
				bmpImage = &dcImage.GetBitmap ();

				CBCGPScanlinerBitmap ms;
				ms.Attach ((HBITMAP) dc.GetBitmap ());
				CBCGPScanlinerBitmap md;
				md.Attach ((HBITMAP) dcImage.GetBitmap ());

				BCGPResizeImage32 (md, sizeDst.cx, sizeDst.cy, ms, size.cx, size.cy, ft);
			}

			CBitmap bitmap;
			bitmap.Attach (CBCGPDrawManager::CreateBitmap_32 (*bmpImage));

			imageDst.AddImage (bitmap, TRUE);
		}
	}
	else
	{
		imageDst.AddImage (imageSrc, index);
	}
}