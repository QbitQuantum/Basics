	bool GetPageBits(CET_LoadInfo *pDecodeInfo)
	{
		bool result = false;

		if (!lWidth || !lHeight)
		{
			pDecodeInfo->nErrNumber = PGE_INVALID_IMGSIZE;
			return false;
		}

		GDIPlusData *pData = (GDIPlusData*)CALLOC(sizeof(GDIPlusData));

		if (!pData)
		{
			pDecodeInfo->nErrNumber = PGE_NOT_ENOUGH_MEMORY;
		}
		else
		{
			pData->nMagic = eGdiStr_Bits;
			pData->pImg = this;
			pDecodeInfo->pFileContext = pData;
			wsprintf(pData->szInfo, L"%i x %i x %ibpp", lWidth, lHeight, nBPP);

			if (nPages > 1) wsprintf(pData->szInfo+lstrlen(pData->szInfo), L" [%i]", nPages);

			if (FormatName[0])
			{
				lstrcat(pData->szInfo, L" ");
				lstrcat(pData->szInfo, FormatName);
			}

			int nCanvasWidth  = pDecodeInfo->crLoadSize.X;
			int nCanvasHeight = pDecodeInfo->crLoadSize.Y;
			BOOL lbAllowThumb = (nFormatID == cfTIFF || nFormatID == cfTIFF || nFormatID == cfEXIF || nFormatID == cfJPEG);
			//&& (lWidth > (UINT)nCanvasWidth*5) && (lHeight > (UINT)nCanvasHeight*5);
			int nShowWidth, nShowHeight;
			CalculateShowSize(nCanvasWidth, nCanvasHeight, nShowWidth, nShowHeight, lbAllowThumb);
			// Получим из EXIF ориентацию
			int nOrient;

			if (!GetExifTagValueAsInt(PropertyTagOrientation, nOrient)) nOrient = 0;

			if (lbAllowThumb && nOrient)
			{
				Gdiplus::GpImage *thmb = NULL;
				// Сразу пытаемся извлечь в режиме превьюшки (полная картинка нам не нужна)
				Gdiplus::Status lRc = gdi->GdipGetImageThumbnail(img, nShowWidth, nShowHeight, &thmb,
				                      (Gdiplus::GetThumbnailImageAbort)DrawImageAbortCallback, gdi);

				if (thmb)
				{
					lRc = gdi->GdipDisposeImage(img);
					img = thmb;
					lRc = gdi->GdipGetImageWidth(img, &lWidth);
					lRc = gdi->GdipGetImageHeight(img, &lHeight);
				}

				// Теперь - крутим
				Gdiplus::RotateFlipType rft = Gdiplus::RotateNoneFlipNone;

				switch(nOrient)
				{
					case 3: rft = Gdiplus::Rotate180FlipNone; break;
					case 6: rft = Gdiplus::Rotate90FlipNone; break;
					case 8: rft = Gdiplus::Rotate270FlipNone; break;
					case 2: rft = Gdiplus::RotateNoneFlipX; break;
					case 4: rft = Gdiplus::RotateNoneFlipY; break;
					case 5: rft = Gdiplus::Rotate90FlipX; break;
					case 7: rft = Gdiplus::Rotate270FlipX; break;
				}

				if (rft)
				{
					lRc = gdi->GdipImageRotateFlip(img, rft);

					if (!lRc)
					{
						lRc = gdi->GdipGetImageWidth(img, &lWidth);
						lRc = gdi->GdipGetImageHeight(img, &lHeight); //-V519
						nCanvasWidth  = pDecodeInfo->crLoadSize.X;
						nCanvasHeight = pDecodeInfo->crLoadSize.Y;
						CalculateShowSize(nCanvasWidth, nCanvasHeight, nShowWidth, nShowHeight, lbAllowThumb);
					}
				}
			}

			nCanvasWidth  = nShowWidth;
			nCanvasHeight = nShowHeight;
			int nCanvasWidthS = nCanvasWidth; //((nCanvasWidth+7) >> 3) << 3; // try to align x8 pixels
			pData->hCompDc1 = CreateCompatibleDC(NULL);
			BITMAPINFOHEADER bmi = {sizeof(BITMAPINFOHEADER)};
			bmi.biWidth = nCanvasWidthS;
			bmi.biHeight = -nCanvasHeight; // Top-Down DIB
			bmi.biPlanes = 1;
			bmi.biBitCount = 32;
			bmi.biCompression = BI_RGB;
			LPBYTE pBits = NULL;
			pData->hDIB = CreateDIBSection(pData->hCompDc1, (BITMAPINFO*)&bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);

			if (!pData->hDIB)
			{
				_ASSERTE(pData->hDIB);
			}
			else
			{
				pData->hOld1 = (HBITMAP)SelectObject(pData->hCompDc1, pData->hDIB);
				RECT rcFull = {0,0,nCanvasWidthS, nCanvasHeight};
				HBRUSH hBr = CreateSolidBrush(pDecodeInfo->crBackground);
				FillRect(pData->hCompDc1, &rcFull, hBr);
				DeleteObject(hBr);
				Gdiplus::GpGraphics *pGr = NULL;
				Gdiplus::Status stat = gdi->GdipCreateFromHDC(pData->hCompDc1, &pGr);

				if (!stat)
				{
#ifdef _DEBUG

					if (nCanvasWidth!=nShowWidth || nCanvasHeight!=nShowHeight)
					{
						_ASSERTE(nCanvasWidth==nShowWidth && nCanvasHeight==nShowHeight);
					}

#endif
					//int x = (nCanvasWidth-nShowWidth)>>1;
					//int y = (nCanvasHeight-nShowHeight)>>1;
					stat = gdi->GdipDrawImageRectRectI(
					           pGr, img,
					           0, 0, nShowWidth, nShowHeight,
					           0, 0, lWidth, lHeight,
					           Gdiplus::UnitPixel, NULL, //NULL, NULL);
					           (Gdiplus::DrawImageAbort)DrawImageAbortCallback, gdi);
					gdi->GdipDeleteGraphics(pGr);
				}

				if (stat)
				{
					pDecodeInfo->nErrNumber = PGE_BITBLT_FAILED;
				}
				else
				{
					result = true;
					pDecodeInfo->pFileContext = (LPVOID)pData;
					pDecodeInfo->crSize.X = nCanvasWidth; pDecodeInfo->crSize.Y = nCanvasHeight;
					pDecodeInfo->cbStride = nCanvasWidthS * 4;
					pDecodeInfo->nBits = 32;
					pDecodeInfo->ColorModel = CET_CM_BGR;
					pDecodeInfo->pszComments = pData->szInfo;
					pDecodeInfo->cbPixelsSize = pDecodeInfo->cbStride * nCanvasHeight;
					pDecodeInfo->Pixels = (const DWORD*)pBits;
				}
			}

			pData->pImg = NULL;

			if (!result)
			{
				pDecodeInfo->pFileContext = this;
				pData->Close();
			}
		}

		return result;
	};