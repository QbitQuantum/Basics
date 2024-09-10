HBITMAP CEnBitmap::LoadImageFile(LPCTSTR szImagePath, COLORREF crBack)
{
	int nType = GetFileType(szImagePath);
	//TRACE("Load(%ws)\n", szImagePath);
	switch (nType)
	{
		// i suspect it is more efficient to load
		// bmps this way since it avoids creating device contexts etc that the 
		// IPicture methods requires. that method however is still valuable
		// since it handles other image types and transparency
		case FT_BMP:
			{
				HBITMAP bmp=(HBITMAP)::LoadImage(NULL, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				BITMAP bi;
				::GetObject(bmp, sizeof( BITMAP ), &bi);

				BYTE bpp = bi.bmBitsPixel >> 3;
				if(bpp==4){
				BYTE* pBits = new BYTE[ bi.bmWidth * bi.bmHeight * bpp ];
				int  p = ::GetBitmapBits( bmp, bi.bmWidth * bi.bmHeight * bpp, pBits);
				for (int y=0; y<bi.bmHeight; ++y)
				{
					BYTE *pPixel= (BYTE *) pBits + bi.bmWidth * 4 * y;
						for (int x=0; x<bi.bmWidth ; ++x)
						{
							pPixel[0]= pPixel[0]*pPixel[3]/255;
							pPixel[1]= pPixel[1]*pPixel[3]/255;
							pPixel[2]= pPixel[2]*pPixel[3]/255;
							pPixel+= 4;
						}
				}
				::SetBitmapBits(bmp, bi.bmWidth*bi.bmHeight*bpp, pBits);
				delete pBits;
				}
				return bmp;
			}

		case FT_UNKNOWN:
			return NULL;

		default: // all the rest
		{
			USES_CONVERSION;
			IPicture* pPicture = NULL;
			
			HBITMAP hbm = NULL;
			HRESULT hr = OleLoadPicturePath(T2OLE((LPTSTR)szImagePath), NULL, 0, crBack, IID_IPicture, (LPVOID *)&pPicture);
					
			if (pPicture)
			{
				hbm = ExtractBitmap(pPicture, crBack);
				pPicture->Release();
			}

			return hbm;
		}
	}

	return NULL; // can't get here
}